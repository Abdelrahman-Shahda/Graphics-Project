//
// Created by 20101 on 1/17/2021.
//
#include <utils/sceneLoader.h>
#include <utils/loadingFunction.h>
SceneLoader::SceneLoader(std::string scenePath) {

    std::ifstream file_in(scenePath);
    file_in >> json;
    file_in.close();
    std::cout << json.dump(4) << std::endl;
	loadMaterial();
}

void SceneLoader::loadMaterial()
{
	nlohmann::json resources=json["resources"];
	std::cout << resources["shaders"];

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
		std::cout << name << "\n";
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
			std::cout << samplerName.dump(3) << "\n";
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

void SceneLoader::loadEntites(nlohmann::json &json) {

    for(auto& [name, child]: json.items()){

        std::shared_ptr<Entity> entity(new Entity);
        std::string tag = child.value<std::string>("tag", "");
        entity->setTag(tag);
        std::cout << entity->withTag("Santa")<<std::endl;
    }

}
shared_ptr<Mesh> SceneLoader::loadMesh(const nlohmann::json&j)
{
	shared_ptr<Mesh> meshObject(new Mesh);
	string val=j.get<std::string>();
	if (val == "cubiod")
		MeshUtils::Cuboid(*meshObject, false);

	else if (val == "sphere")
		MeshUtils::Sphere(*meshObject);

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

