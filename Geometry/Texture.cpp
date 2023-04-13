//
// Created by anna on 20/01/2020.
//

#include "Texture.h"

Texture::Texture(QString nomfitxer)
{
    bool success = image.load(nomfitxer);
    if (!success) std::cout << "Imatge no trobada" << endl;
}

Texture::~Texture() {

}
vec3 Texture::getColorPixel(vec2 uv) {

    QColor c(image.pixel(glm::trunc((uv.x)*image.width()), glm::trunc((uv.y)*image.height() )));
    vec3 a = (vec3(c.redF(), c.greenF(), c.blueF()));
    return a;
}
