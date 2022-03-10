/*
 * Проекты часто разрабатываются с использованием разных языков, JSON -- формат обмена данными,
 * позволяющий, например, передавать данные в формате контейнера одного языка в другой (например, map
 * в C++ в dict в Python)
 */

/*
 * <filesystem> позволяет работать с файловой системой из кода программы, создавать директории,
 * копировать и удалять файлы, проводить итерации по содержимому каталога
 */

#include <iostream>
#include <map>
#include <filesystem>
#include <fstream>
#include "json.hpp"

class Account
{
private:
    std::string users_name;
    unsigned int users_age;
    std::string marital_status;
    bool online;
    bool has_relatives=false;
    std::map<std::string,std::string> relatives;

public:
    Account() = default;
    Account(std::string user_name, unsigned int users_age, std::string marital_status, bool online):
    users_name(user_name),users_age(users_age), marital_status(marital_status), online(online) {} ;

    void AddRelative(std::string relatives_name, std::string relation)
    {
        relatives[relatives_name]=relation;
    }

    std::string UsersName()
    {
        return users_name;
    }
    unsigned int UsersAge()
    {
        return users_age;
    }
    std::string MaritalStatus()
    {
        return marital_status;
    }
    bool Online()
    {
        return online;
    }
    bool HasRelatives()
    {
        return !(relatives.empty());
    }
    std::map<std::string,std::string> Relatives()
    {
        return relatives;
    }
    ~Account()=default;
};

int main() {
    Account u1("Janine Minkovski", 25, "engaged", true);
    u1.AddRelative("Mary Loo Minkovski", "Sister-in-Law");
    u1.AddRelative("Jonathan Minkovski", "Brother");
    u1.AddRelative("Jenifer Allison", "fiancee");
    nlohmann::json u1_data = {
            {"name", u1.UsersName()},
            {"Age", u1.UsersAge()},
            {"Marital Status", u1.MaritalStatus()},
            {"Is online?", u1.Online()},
    };
    if(u1.HasRelatives())
        for(auto [relatives_name, relatives_status]: u1.Relatives())
            u1_data["relatives"][relatives_name] = relatives_status;
    std::cout<<u1_data.dump(4)<<"\n";

    std::filesystem::path parent_dir("..");
    auto saving_dir = parent_dir/"Users";
    std::filesystem::create_directories(saving_dir);

    std::fstream inNout(std::filesystem::absolute(saving_dir/"User1.json"), std::ios::out);
    inNout<<std::setw(4)<<u1_data<<"\n";
    inNout.close();

    Account u2("Juan Gomez", 30, "married", true);
    u2.AddRelative("Julio Gonzales", "Cousin");
    u2.AddRelative("Adrian Gomez", "Brother");
    u2.AddRelative("Jesus Gomez", "Brother");
    u2.AddRelative("Camilo Gomez", "Brother");
    u2.AddRelative("Carlos Gomez", "Brother");
    u2.AddRelative("Renzo Gomez", "Brother");
    u2.AddRelative("Roberto Gomez", "Brother");
    u2.AddRelative("Sabrina Gomez", "Sister");
    u2.AddRelative("Alexandro Gomez", "Husband");
    nlohmann::json u2_data = {
            {"name", u2.UsersName()},
            {"Age", u2.UsersAge()},
            {"Marital Status", u2.MaritalStatus()},
            {"Is online?", u2.Online()},
    };

    if(u2.HasRelatives())
        for(auto[name,relation]: u2.Relatives()) u2_data["relatives"][name]=relation;

    std::cout<<"\n";

    inNout.open(std::filesystem::absolute(saving_dir/"User2.json"), std::ios::out);
    inNout<<std::boolalpha<<std::setw(4)<<u2_data<<"\n";
    inNout.close();
    std::cout<<u2_data.dump(4)<<"\n";

    return 0;
}
