//
// Created by leo on 25/12/22.
//

#ifndef TRASHENGINE_MATERIAL_HPP
#define TRASHENGINE_MATERIAL_HPP

#endif //TRASHENGINE_MATERIAL_HPP

class Material {
    vector3f color;
public:
    Texture texture;
    Material(const Texture& texture, const vector3f& color);
};

Material::Material(const Texture& texture, const vector3f& color):
    texture(texture),
    color(color)
{}
