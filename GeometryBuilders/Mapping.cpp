#include "Mapping.h"

Mapping::Mapping(shared_ptr<ConfigMappingReader> mr)
{
   setup = mr;
}


vec3 Mapping::mapeigPunt(vec3 puntMonReal) {
    // TO DO Fase 1:
    // Mapeig del punt en coordenades reals a coordenades de mon virtual
    // Cal posar el codi per a situar el punt del mon Real al Virtual
    // Cal canviar la següent línia
      vec3 puntMonVirtual;

      puntMonVirtual.x = (((puntMonReal.x - this->setup->Rxmin) / (this->setup->Rxmax - this->setup->Rxmin)) *
                         (this->setup->Vxmax - this->setup->Vxmin)) + this->setup->Vxmin;
      puntMonVirtual.y = puntMonReal.y;
      puntMonVirtual.z = (((puntMonReal.z - this->setup->Rzmin) / (this->setup->Rzmax - this->setup->Rzmin)) *
                         (this->setup->Vzmax - this->setup->Vzmin)) + this->setup->Vzmin;
      puntMonVirtual.z = -puntMonVirtual.z;
  
      if (this->setup->Rymax != this->setup->Rymin)
         puntMonVirtual.y = (((puntMonReal.y - this->setup->Rymin) / (this->setup->Rymax - this->setup->Rymin)) *
                            (this->setup->Vymax - this->setup->Vymin)) + this->setup->Vymin;

      return puntMonVirtual;
}

float Mapping::mapeigValor(float valorMonReal) {
    // TO DO Fase 1:
    // Mapeig del valor en dimensions reals a dimensions de mon virtual
    // Cal canviar la següent línia
    double valorMonVirtual;

    //valorMonVirtual = (valorMonReal - this->setup->Rxmin) / (this->setup->Rxmax - this->setup->Rxmin);
    valorMonVirtual = valorMonReal;
    return valorMonVirtual;
}

float Mapping::mapeigValor(float valorMonReal, int i) {
    // TO DO Fase 1:
    // Mapeig del valor en dimensions reals a dimensions de mon virtual
    // Cal canviar la següent línia
    double valorMonVirtual;

    valorMonVirtual = (valorMonReal - this->setup->propLimits[i].first) /
                      (this->setup->propLimits[i].second - this->setup->propLimits[i].first);
    return valorMonVirtual;
}

shared_ptr<ColorMap> Mapping::getColorMap(ColorMapStatic::COLOR_MAP_TYPES tCM) {
   shared_ptr<ColorMapStatic> cm = make_shared<ColorMapStatic>(tCM);
   return cm;
}

shared_ptr<Material> Mapping::mapeigMaterial(int i, ColorMapStatic::COLOR_MAP_TYPES tCM, double valorMonReal) {

    // TO DO Fase 2: Cal mapejar el color difus al color de la paleta o ColorMap segons el valorMonReal i
    // els valors minims i maxims de les propietats
    // Tens els valors minims i maxim de cada propietat a l'estructura de setup d'aquesta classe

    auto cm = getColorMap(tCM);
    int idx = 255*int(valorMonReal/(setup->propLimits[i].second-setup->propLimits[i].first));
    //return make_shared<Metal>();
    return make_shared<Transparente>(cm->getColor(idx));
}
