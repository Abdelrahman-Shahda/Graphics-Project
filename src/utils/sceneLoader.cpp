//
// Created by 20101 on 1/17/2021.
//
#include <utils/sceneLoader.h>
#include <utils/loadingFunction.h>
SceneLoader::SceneLoader(std::string scenePath) {

    std::ifstream file_in(scenePath);
    file_in >> json;
    file_in.close();
    //std::cout << json.dump(4) << std::endl;
	loadMaterial();
}

void SceneLoader::loadMaterial()
{
	nlohmann::json resources=json["resources"];
	//std::cout << resources["shaders"];

	//Materials maps
	unordered_map<string, shared_ptr<Resources::ShaderProgram>> shadersMap;
	unordered_map<string, shared_ptr<Resources::Sampler>> samplersMap;
	unordered_map<string, shared_ptr<Resources::Texture>> texturesMap;

	//loading shaders
	for (auto &[name,shader] : resources["shaders"].items())
		shadersMap[name] = loadShader(shader);

	//loading samplers
	for (auto &[name, sampler] : resources["samplers"].items())
	{
		//std::cout << name << "\n";
		samplersMap[name] = loadSampler(sampler);
	}

	//loading Meshes
	for (auto &[name, mesh] : resources["meshes"].items())
		meshesMap[name] = loadMesh(mesh);

	//loading Textures
	for (auto &[name, text] : resources["textures"].items())
		texturesMap[name] = loadTexture(text);

	//loading material
	for (auto &[name, materialCotent] : resources["materials"].items())
	{
		string shaderName = materialCotent.value("shader", "defaultShader");
		shared_ptr<Material> materialPtr(new Material(shadersMap[shaderName]));

		//adding textures to material
		for (auto &[textureName, samplerName] : materialCotent["textures"].items())
		{
			//std::cout << samplerName.dump(3) << "\n";
			materialPtr->addTexture(texturesMap[textureName], samplersMap[samplerName.get<string>()]);
		}
		materialsMap[name] = materialPtr;
	}

}

shared_ptr<Texture> SceneLoader::loadTexture(nlohmann::json &j)
{
	string path = j.value("path", "");
	bool mipmap = j.value("mipmap", true);
	string type = j.value("type", "albedo");
	path = ASSETS_DIR"/image/material/" + path;
	shared_ptr<Texture> textureObject(new Texture(type, path.c_str(), mipmap));
	return textureObject;
}
shared_ptr<Entity> SceneLoader::loadSky() {

    shared_ptr<Entity> skyLight(new Entity);
    glm::vec3 top_color = json["SkyLight"].value<glm::vec3>("top_color", {0,0,0});
    glm::vec3 middle_color = json["SkyLight"].value<glm::vec3>("middle_color", {0.5,0.5,0.5});
    glm::vec3 bottom_color = json["SkyLight"].value<glm::vec3>("bottom_color", {1,1,1});
    bool enabled = json["SkyLight"].value("enabled", true);
    skyLight->addComp<SkyLight, bool, glm::vec3, glm::vec3, glm::vec3>(enabled, top_color, middle_color, bottom_color);
    skyLight->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshesMap["cuboid"], materialsMap["skyMaterial"]);
    skyLight->addComp<RenderState,bool,bool>(true,true);

    //
    std::shared_ptr<SkyLight> skyLightComponent = skyLight->getComp<SkyLight>();
    shared_ptr<Resources::ShaderParameter<glm::vec3>> skyLightTopColor(new ShaderParameter<glm::vec3>("sky_light.top_color", skyLightComponent != NULL && skyLightComponent->enabled ? skyLightComponent->top_color : glm::vec3(0.0f)));
    shared_ptr<Resources::ShaderParameter<glm::vec3>> skyLightMiddleColor(new ShaderParameter<glm::vec3>("sky_light.middle_color", skyLightComponent != NULL && skyLightComponent->enabled ? skyLightComponent->middle_color : glm::vec3(0.0f)));
    shared_ptr<Resources::ShaderParameter<glm::vec3>> skyLightBottomColor(new ShaderParameter<glm::vec3>("sky_light.bottom_color", skyLightComponent != NULL && skyLightComponent->enabled ? skyLightComponent->bottom_color : glm::vec3(0.0f)));
    shared_ptr<Resources::ShaderParameter<float>> skyExposure(new ShaderParameter<float>("exposure", 2.0f));



    for (auto const& [key, val] : materialsMap)
    {
        val->addShaderParameter(skyLightTopColor);
        val->addShaderParameter(skyLightBottomColor);
        val->addShaderParameter(skyLightMiddleColor);
        val->addShaderParameter(skyExposure);
    }

    return skyLight;
}
void SceneLoader::loadComponent(std::string component, nlohmann::json &json, std::shared_ptr<Entity> en,Application* application,std::vector<std::shared_ptr<Entity>> &entities) {


    if(component == "MeshRenderer"){

        shared_ptr<Resources::Mesh> meshPtr = meshesMap[json.value<std::string>("mesh", "")];
        shared_ptr<Resources::Material> materialPtr = materialsMap[json.value<std::string>("material", "")];
        std::cout << "Added Mesh"<<std::endl;
        en->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshPtr, materialPtr);
    }else if(component == "Player"){
        en->addComp<Player>();
        std::shared_ptr<Transform> ptr = en->getComp<Transform>();
        for(int i = 0 ; i < 3;i++){
            shared_ptr<Entity> heart(new Entity("Life"));
            heart->addComp<MeshRenderer, shared_ptr<Mesh>, shared_ptr<Resources::Material>>(meshesMap["heart"], materialsMap["heartMaterial"]);
            heart->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>({ -35 -( 5*i), 60, 50 }, { 3*3.14/2,0 , 0 }, { 0.05, 0.05,  0.05 });
            heart->getComp<Transform>()->update();
            heart->addComp<RenderState,bool>(true);
            heart->getComp<Transform>()->set_parent(ptr);
            ptr->add_child( heart->getComp<Transform>());
            entities.push_back(heart);
        }
    }else if(component == "Camera"){
        std::shared_ptr<Camera> cameraPtr = en->addComp<Camera>();
        en->addComp<FlyCameraController, Application*,std::shared_ptr<Camera>>(application,cameraPtr,en->getComp<Transform>());
    }else if(component == "RenderState"){

       bool isVisible = json.value("isVisible",true);
       bool blendingEnabled = json.value("blendingEnabled", true);
       en->addComp<RenderState,bool,bool>(isVisible,blendingEnabled);
    }else if(component == "Gift"){
        int points = json.value("points", 10);
        en->addComp<Gift,int>(points);
    }else if(component == "Light"){
        std::string type_name = json.value("type", "point");
        LightType type;
        if(type_name == "directional") type = LightType::DIRECTIONAL;
        else if(type_name == "spot") type = LightType::SPOT;
        else type = LightType::POINT;
        glm::vec3 color = json.value<glm::vec3>("color", {1,1,1});
        glm::vec3 direction = json.value<glm::vec3>("direction", {0, -1, 0});
        glm::vec3 position = json.value<glm::vec3>("position", {0,0,0});

        bool enabled = json.value<bool>("enabled", true);
        //Attenuation
        float constant = json.value("constant", 0.0f);
        float linear = json.value("linear", 0.0f);
        float quadratic = json.value("quadratic", 1.0f);

        //Spot Angle
        float inner = json.value("inner", glm::quarter_pi<float>());
        float outer = json.value("outer", glm::half_pi<float>());

        en->addComp<Light,LightType,glm::vec3, bool,float,float,float,float,float>(type,color, enabled,constant,linear,quadratic,inner,outer);

    }else if(component == "Elf"){
        int points = json.value("points", 10);
        en->addComp<Elf,int>(points);
    }

}
void SceneLoader::loadEntites(Application *application,nlohmann::json &j, std::shared_ptr<Transform> parent,std::vector<std::shared_ptr<Entity>> &entities) {

    std::shared_ptr<Entity> entity(new Entity);
    std::string tag = j.value<std::string>("tag", "");
    entity->setTag(tag);

    //Taking the value of Transform Component
    //std::cout<<j.dump(4)<<std::endl;
    glm::vec3 position = j.value<glm::vec3>("position", {0.0,0.0,0.0});
    glm::vec3 rotation = j.value<glm::vec3>("rotation", {0.0,0.0,0.0});
    glm::vec3 scale = j.value<glm::vec3>("scale", {0.0,0.0,0.0});

    std::shared_ptr<Transform> enTr = entity->addComp<Transform, glm::vec3, glm::vec3, glm::vec3>(position,rotation,scale);
    enTr->update();
    if(parent !=NULL){
        std::cout <<"Ba2olak eh shahda gamed"<<std::endl;
        parent->add_child(enTr);
    }
    enTr->set_parent(parent);
    for(auto&[component, js]:j["components"].items() ){
        loadComponent(component, js, entity,application,entities);
    }
    entities.push_back(entity);
    for(auto&[children, js]:j["children"].items() ){
        shared_ptr<Transform> parentTr = entity->getComp<Transform>();
        loadEntites(application,js,parentTr,entities);
    }
}
std::vector<std::shared_ptr<Entity>> SceneLoader::loadEntities(Application* application) {

    std::vector<std::shared_ptr<Entity>> entities;
    for(auto& [name, j]: json["Scene"].items()){
        loadEntites(application,j,NULL,entities);
    }
    return entities;

}
shared_ptr<Mesh> SceneLoader::loadMesh(const nlohmann::json&j)
{
	shared_ptr<Mesh> meshObject(new Mesh);
	string val=j.get<std::string>();
	if (val == "cuboid")
		MeshUtils::Cuboid(*meshObject, false);

	else if (val == "sphere")
		MeshUtils::Sphere(*meshObject);
    else if (val == "plane")
        MeshUtils::Plane(*meshObject,{1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});
	//If a path is given, load obj file
	else
	{
		string path = ASSETS_DIR"/models/" + val;
		MeshUtils::loadOBJ(*meshObject, path.c_str());
	}

	return meshObject;
}

shared_ptr<Sampler> SceneLoader::loadSampler(const nlohmann::json& j)
{
	GLenum wrap_s = enumsTable.find(j.value("wrap_s", "GL_REPEAT"))->second;
	GLenum wrap_t = enumsTable.find(j.value("wrap_t", "GL_REPEAT"))->second;
	GLenum magnification = enumsTable.find(j.value("magnificationFilter", "GL_LINEAR"))->second;
	GLenum minifcation = enumsTable.find(j.value("minificationFilter", "GL_LINEAR"))->second;
	//TODO:: border color j.value<glm::vec4>("translation", { 0, 0, 0 });

	shared_ptr<Sampler> sampler(new Sampler(wrap_s, wrap_t, minifcation, magnification));
	return sampler;
}

shared_ptr<ShaderProgram> SceneLoader:: loadShader(const nlohmann::json& j)
{
	string vertexShaderPath = j.value("vert", "light_transform.vert");
	string fragmentShaderPath = j.value("frag", "light_array.frag");
	vertexShaderPath = ASSETS_DIR"/shaders/" + vertexShaderPath;
	fragmentShaderPath = ASSETS_DIR"/shaders/" + fragmentShaderPath;

	//string dir = ASSETS_DIR;
	shared_ptr< Resources::ShaderProgram> shaderProgram(new ShaderProgram);
	shaderProgram->create();
	shaderProgram->attach(vertexShaderPath, GL_VERTEX_SHADER);
	shaderProgram->attach(fragmentShaderPath, GL_FRAGMENT_SHADER);
	shaderProgram->link();
	return shaderProgram;
}

