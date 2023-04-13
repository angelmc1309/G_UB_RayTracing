#include "RayTracing.h"



// Metode raytracing principal

// Aquesta funcio transforma cada pixel a coordenades de mon i
// envia un raig des de la camera en aquella direccio cridant al metode CastRay
// i pel pintar la imatge final:
// 1) Neteja la pantalla per a visualitzar el nou frame
// 2) Envia un raig a l'escena per a cada pixel de la pantalla i utilitza el color retornat per a pintar el pixel
// 3) Actualitza la sortida corresponent segons la implementació del mètode setPixelColor de cada fill

//Precondicio:
// La Scene ha d'estar creada i inicialitzada

void RayTracing::rendering() {

    int numSamples = 50;
    int depth = 5;

    // Recorregut de cada pixel de la imatge final
    for (int y = cam->viewportY-1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;  // Progrés del càlcul
        for (int x = 0; x < cam->viewportX; x++) {
            vec3 sumColors = vec3(0,0,0);
            for(int i = 0; i< numSamples;i++){
                vec3 col(0, 0, 0);
                float u = float(x) / float(cam->viewportX);
                float v = float(y) / float(cam->viewportY);

                Ray r = cam->getRay(u, v);

                sumColors += scene->ComputeColor(r, depth);
            }
            sumColors = sumColors * (float)(1.0/numSamples);
            vec3 col = glm::clamp(sumColors,0.0,1.0);
            setPixelColor(vec3(sqrt(col.x),sqrt(col.y),sqrt(col.z)), x, y);
        }
    }
    std::cerr << "\nDone.\n";
}

void RayTracing::exitRender() {

}

// Metode de suport que fa el rendering per a tots els Renders que no usen GLUT
void RayTracing::startRendering(int argc, char **argv) {
    renderingScene();
}

void RayTracing::renderingScene()  {
    initRender(filename.toStdString());
    rendering();
    exitRender();
}

void RayTracing::setCamera(shared_ptr<Camera> c) {
    cam = c;
}
void RayTracing::setScene(shared_ptr<Scene> s) {
    scene = s;
}

void RayTracing::setOutputFile(QString output) {
    filename = output;
}



