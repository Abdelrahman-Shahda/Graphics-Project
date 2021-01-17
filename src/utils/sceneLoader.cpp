//
// Created by 20101 on 1/17/2021.
//
#include <utils/sceneLoader.h>

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
	unordered_map<string, shared_ptr<Resources::Sampler>> meshesMap;

	//loading shaders
	for (auto &[name,shader] : resources["shaders"].items())
	{
		shared_ptr<Resources::ShaderProgram> shaderProgram=loadShader(shader);
		shadersMap[name] = shaderProgram;
	}

	//loading samplers
	for (auto &[name, sampler] : resources["samplers"].items())
	{
		shared_ptr<Resources::Sampler> samplerObject = loadSampler(sampler);
		samplersMap[name] = samplerObject;
	}

	//loading Meshes
	for (auto &[name, mesh] : resources["meshes"].items())
	{
		std::cout << mesh;
		shared_ptr<Mesh> meshObject = loadMesh(mesh);
		meshesMap[name] = meshObject;
	}

	//loading shader parameters


	//loading material
	for (auto &[name, materialCotent] : resources["materials"].items())
	{
		string shaderName = materialCotent.value("shader", "defaultShader");
		shared_ptr<Material> materialPtr(new Material(shadersMap[shaderName]));


	}

}

shared_ptr<Mesh> SceneLoader::loadMesh(const nlohmann::json&j)
{
	shared_ptr<Mesh> meshObject(new Mesh);
	if (j == "cubiod")
		MeshUtils::Cuboid(*meshObject, false);

	else if (j == "sphere")
		MeshUtils::Sphere(*meshObject);

	//If a path is given, load obj file
	else
	{
		string path = ASSETS_DIR"/models/" + j;
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

