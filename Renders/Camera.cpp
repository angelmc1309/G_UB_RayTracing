#include "Camera.h"

Camera::Camera() {
    float aspect = 1;
    viewportX = 400;
    viewportY = 400;
    auto vup = vec3(0,1,0);
    auto lookat = vec3(0,0,0);
    auto lookfrom = vec3(0,0,10);

    float theta = M_PI/2.0f;
    float window_height = 2*tan(theta/2);
    float window_width = aspect * window_height;
    origin = lookfrom;

    w = normalize(lookfrom - lookat);
    u = normalize(cross(vup, w));
    v = cross(w, u);
    float half_width = window_width/2.0f;
    float half_height = window_height/2.0f;
    lower_left_corner = origin  - half_width*u -half_height*v - w;
    horizontal = window_width*u;
    vertical = window_height*v;

}


Camera::Camera(
            vec3 lookfrom,
            vec3 lookat,
            vec3   vup,
            double vfov, // vertical field-of-view in degrees
            double aspect_ratio, double pixelsX)
{
    auto theta = (vfov)*M_PI/180.0f;
    auto h = tan(theta/2);
    float window_height = 2.0f * h;
    float window_width = aspect_ratio * window_height;

    w = normalize(lookfrom - lookat);
    u = normalize(cross(vup, w));
    v = cross(w, u);



    origin = lookfrom;

    //focus_dist = glm::length(origin-lookat);
    focus_dist = 1; //Without Defocus Blur

    horizontal = (window_width * u);
    vertical = (window_height * v);
    float half_width = window_width/2.0f;
    float half_height = window_height/2.0f;

    lower_left_corner = origin  - (half_width)*u*focus_dist
            -(half_height)*v*focus_dist - focus_dist * w;
/*
    horizontal = 2*focus_dist*window_width*u;
    vertical = 2*focus_dist*window_height*v;
*/
    //  Without Defocus Blur
    horizontal = window_width*u;
    vertical = window_height*v;


    viewportX = pixelsX;
    viewportY = pixelsX/aspect_ratio;

    this->aperture = 0.5;

    lens_radius = aperture / 2;
}


Ray Camera::getRay(float s, float t) {
    vec3 rd = lens_radius * this->random_in_unit_disk();
    vec3 offset = u * rd.x + v * rd.y;

    // To take out Defocus Blur extract offset
    return Ray(origin , lower_left_corner + s*horizontal +
                t*vertical - origin );
}

