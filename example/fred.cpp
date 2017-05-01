#include "fred.h"
#include <sstream>

Fred::Fred()
{

}

void Fred::serialize(std::string &out_string) const
{
    std::ostringstream oss;
    oss << relax << "|" << couch << "|" << surf;
    out_string = oss.str();
}

void Fred::deserialize(const std::string &in_string)
{
    std::string::size_type relax_end_pos = in_string.find("|");
    std::string::size_type couch_end_pos = in_string.find("|", relax_end_pos + 1);

    std::string relax_str = in_string.substr (0,relax_end_pos);
    std::string couch_str = in_string.substr (relax_end_pos + 1, couch_end_pos - relax_end_pos - 1);
    std::string surf_str = in_string.substr (couch_end_pos + 1, in_string.length() - couch_end_pos - 1);

    std::stringstream ss;
    ss << relax_str;
    ss >> relax;
    ss.str("");
    ss.clear();
    ss << couch_str;
    ss >> couch;
    ss.str("");
    ss.clear();
    ss << surf_str;
    ss >> surf;
    ss.str("");
    ss.clear();

}

int Fred::get_relax() const
{
    return relax;
}

void Fred::set_relax(int value)
{
    relax = value;
}

double Fred::get_couch() const
{
    return couch;
}

void Fred::set_couch(double value)
{
    couch = value;
}

int Fred::get_surf() const
{
    return surf;
}

void Fred::set_surf(int value)
{
    surf = value;
}

std::ostream& operator<<(std::ostream& out, const Fred& fred)
{
    out << "relax: " <<  fred.get_relax() << std::endl;
    out << "couch: " << fred.get_couch() << std::endl;
    out << "surf: " << fred.get_surf() << std::endl;

   return out;
}
