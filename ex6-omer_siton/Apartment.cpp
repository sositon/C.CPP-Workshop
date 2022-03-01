//
// Created by omer siton on 19/12/2021.
//

#include <valarray>
#include "Apartment.h"

Apartment::Apartment (const std::pair<double, double> &Coordinates):
_x(Coordinates.first) , _y(Coordinates.second)
{}
double Apartment::get_x () const
{
  return _x;
}
double Apartment::get_y () const
{
  return _y;
}
bool Apartment::operator< (const Apartment &other) const
{
  return this->get_distance_from_feelbox() < other.get_distance_from_feelbox();
}
bool Apartment::operator> (const Apartment &other) const
{
  return this->get_distance_from_feelbox() > other.get_distance_from_feelbox();
}
bool Apartment::operator== (const Apartment &other) const
{
  return std::abs (_x - other.get_x()) <= EPSILON &&
         std::abs (_y - other.get_y()) <=EPSILON;
}
std::ostream &operator<< (std::ostream &os, const Apartment &apartment)
{
  os << "(" << apartment.get_x() << "," << apartment.get_y() << ")" <<std::endl;
  return os;
}
double Apartment::get_distance_from_feelbox () const
{
  return std::sqrt (std::pow ((_x - X_FEEL_BOX), 2) +
                    std::pow ((_y - Y_FEEL_BOX), 2));
}
