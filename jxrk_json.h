#ifndef JSON_JXRK_LIB
#define JSON_JXRK_LIB

#include <fstream>
#include <map>

using std::string, std::fstream,  std::to_string, std::map;

struct any {
    void* pointer;

    any() {}

    template <typename T>
    any(const T& object) {
        pointer = (void*)&object;
    }
    
    template <typename T>
    T& get() {
        return *(T*)pointer;
    }
};

class JSON {
    private:
        int tabs = 0;
        bool tab = false;
        fstream file;
        map<string, any> dict;
    public:
        JSON() {}

        template <typename T>
        string json_type(const T& object) {
            return to_string(object);
        }

        string json_type(const char* object) {
            if (!*object) {
                return "";
            }
            return json_type(string(object));
        }

        string json_type(const string& object) {
            return ('"' + object + '"');
        }

        string json_type(const bool& object) {
            if (object) return "true";
            return "false";
        }

        void open(const string& path, const std::ios::openmode& flag) {
            file.open(path, flag);
        }

        void close() {
            if (tabs) {
                throw ('1');
            }
            file.close();
        }

        void reset_streampos() {
            file.seekg(0);
        }

        void section_open() {
            if (!file.is_open()) return;
            if (tab) {
                for (int i = 0; i < tabs; i++) {
                    file << '\t';
                }
            }
            tabs++;
            file << "{\n";
            tab = true;
        }

        void section_close() {
            if (!file.is_open()) return;
            tabs--;
            file << '\n';
            for (int i = 0; i < tabs; i++) {
                file << '\t';
            }
            file << '}';
            tab = false;
        }

        template <typename T>
        void write(const string& key, const T& var) {
            if (!file.is_open()) return;
            if (!tab) {
                file << ",\n";
            }
            for (int i = 0; i < tabs; i++) {
                file << '\t';
            }
            file << json_type(key) << ": " << json_type(var);
            tab = false;
        }

        template <typename T>
        T get(const string& key) {
            T temp;
            find(key, temp); // some function that overrides temp
            return temp;
        }

        template <typename T>
        T get_next(const string& key) {
            T temp;
            find_next(key, temp); // some function that overrides temp
            return temp;
        }

        void find_next(const string& key, string& var) {
            if (!file.is_open()) return;
            string first, second;
            char iter;
            while (file >> iter) {
                switch (iter) {
                case '"':
                    getline(file, first, '"');
                    break;
                case ':':
                    file >> std::noskipws >> iter >> iter;
                    if (iter == '"') {
                        getline(file, second, '"');
                    }
                    else {
                        continue;
                    }
                    if (first == key || key.empty()) {
                        var = second;
                        return;
                    }
                    break;
                default:
                    break;
                }
            }
        }

        template<typename T>
        void find(const string& key, T& var) {
            reset_streampos();
            find_next(key, var);
        }

        template<typename T> 
        void find_next(const string& key, T& var) {
            if (!file.is_open()) return;
            string first;
            T second;
            char iter;
            while (file >> iter) {
                switch (iter) {
                case '"':
                    getline(file, first, '"');
                    break;
                case ':':
                    file >> std::noskipws >> iter;
                    if (file.peek() == '{') {
                        continue;
                        break;
                    }
                    if (first == key) {
                        file >> second;
                        var = second;
                        return;
                    }
                    break;
                default:
                    break;
                }
            }
        }

        ~JSON() {
            this->close();
        }
};

/*
    json.open(path, std::ios::out);

    json.section_open();
    
    json.write("name", "Knight");
    
    json.write("hp_comp", "");
    json.section_open();
    json.write("hp", 30);
    json.write("max_hp", 30);
    json.section_close();

    json.write("weapon_comp", "");
    json.section_open();
    json.write("weapon_name", "Sword");
    json.write("weapon_damage", 4);
    json.write("crit_coeff", 10);
    json.write("crit_multiplier", 3);
    json.section_close();

    json.write("current_score", 0);
    json.write("highest_score", 0);
    json.write("enemy_id", 0);
    json.write("enemy_impact", 0);
    json.write("hash", "3349519565436290102");
    
    json.section_close();

    json.close();
*/

#endif