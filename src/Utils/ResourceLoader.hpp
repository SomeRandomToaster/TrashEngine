//
// Created by leo on 21/12/22.
//

#ifndef TRASHENGINE_RESOURCELOADER_HPP
#define TRASHENGINE_RESOURCELOADER_HPP

#endif //TRASHENGINE_RESOURCELOADER_HPP

class ResourceLoader {
public:
    ResourceLoader(const string& textureFileName);
    Mesh mesh;
    Material material;
};
ResourceLoader::ResourceLoader(const string& textureFileName) :
    material(Texture(textureFileName), vector3f(1, 1, 1))
{}
