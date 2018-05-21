#include "getargs.h"


using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::set;


bool match(char const *needle, char const *haystack) {
    bool brackets = false;
    set<char> avaliable_chars; 
    for (; *needle != '\0'; ++needle) {
        switch (*needle) {
        case '[': {
            brackets = true;
            continue;
        }
        case ']': {
            brackets = false;
            if(avaliable_chars.find(*haystack) == avaliable_chars.end()){
                return false;
            }
            avaliable_chars.clear();
        }
        case '?': 
            if (*haystack == '\0')
                return false;
            ++haystack;
            break;
        case '*': {
            if (needle[1] == '\0')
                return true;
            size_t max = strlen(haystack);
            for (size_t i = 0; i < max; i++)
                if (match(needle + 1, haystack + i))
                    return true;
            return false;
        }
        default:
            if (brackets){
                avaliable_chars.insert(*needle);
                continue;
            }
            if (*haystack != *needle)
                return false;
            ++haystack;
        }
    }
    return *haystack == '\0';
}


vector<string> wildcard(string matched, string path){
    vector<string> result;
    struct dirent **namelist;
    int n;
    n = scandir(path.c_str(), &namelist, 0, alphasort);
    if (n < 0)
        return result;
    else {
        while(n--) {

        if(strcmp(namelist[n]->d_name, ".") != 0 && strcmp(namelist[n]->d_name, "..") != 0)
            
            if(match(matched.c_str(), namelist[n]->d_name)){
                result.push_back(namelist[n]->d_name);
            }
            
            free(namelist[n]);
        
        }
        free(namelist);
    }
    return result;
}

string substitude_variables(string input, vm::VariablesMap &variables){
    bool single_quotes_opened = false, double_quotes_opened = false, var_started = false;
    string result = "";
    string var = "";
    for(auto c: input){
        if(c == '\'' && !double_quotes_opened){
            single_quotes_opened = !single_quotes_opened;
        }
        if(c == '\"' && !single_quotes_opened){
            double_quotes_opened = !double_quotes_opened;
        }
        if(c == '$' && !single_quotes_opened){
            var_started = true;
            continue;
        }
        if(var_started){
            if(!isalpha(c)){
                if(variables.contains(var)){
                    result += variables.get(var);
                }else{
                    result += "$" + var;
                }
                var = "";
                var_started = false;
            }else{
                var += c;
            }
        }
        if(!var_started){
            result += c;
        }
    }
    if(var_started){
        if(variables.contains(var)){
            result += variables.get(var);
        }else{
            result += "$" + var;
        }
    }
    return result;
}

string ignore_comments(string input){
    string curr_word = "";
    bool next_escaped = false;
    bool single_quotes_opened = false, double_quotes_opened = false;
    for(int i = 0; i < input.size(); i++){
        curr_word += input[i];
        if(next_escaped){
            next_escaped = false;
            continue;
        }
        if(input[i] == '\\'){
            next_escaped = true;
            continue;
        }

        if(input[i] == '\''){
            single_quotes_opened = !single_quotes_opened;
            continue;
        }
        if(input[i] == '"'){
            double_quotes_opened = !double_quotes_opened;
            continue;
        }
        if(input[i] == '#' && !single_quotes_opened && !double_quotes_opened){
            return curr_word.substr(0, curr_word.size()-1);
        }
  }
  return curr_word;
}


vector<arguments::Arguments> get_args(string input, vm::VariablesMap &variables) {
    input = ignore_comments(input);
    input = substitude_variables(input, variables);
	input += " "; // Add last checking
    vector<string> result;
	vector<string> seperators;
    string basec, regex, path, cpy;
    string curr_word = "";
    bool next_escaped = false;
    bool single_quotes_opened = false, double_quotes_opened = false;
    bool replacing = true;
    bool is_flag = false;

	string tmp_str;
	seperators.push_back(" ");

    
    for(int i = 0; i < input.size(); i++){

		// wildcard support
		if(seperators.size() <= result.size() ){
			for(int l = 0; l < result.size() - seperators.size() + 1; l++){
				seperators.push_back(" ");
			}
		}


        if(next_escaped){
            curr_word += input[i];
            next_escaped = false;
            continue;
        }
        if(input[i] == '\\'){
            next_escaped = true;
            continue;
        }

        if(input[i] == '\''){
            single_quotes_opened = !single_quotes_opened;
            replacing = false;
            continue;
        }
        if(input[i] == '"'){
            double_quotes_opened = !double_quotes_opened;
            continue;
        }

        if((input[i] == ' ' || input[i] == '>' || input[i] == '<' || input[i] == '|') 
		&& !single_quotes_opened && !double_quotes_opened){
                if(curr_word.size() > 0){
                    if(replacing && !is_flag && result.size() > 0){

                        cpy = curr_word;
                        basec = strdup(const_cast<char*>(cpy.c_str()));
                        path = dirname(const_cast<char*>(cpy.c_str()));
                        regex = basename(const_cast<char*>(basec.c_str()));

                        vector<string> matched = wildcard(regex, path);
                        
                        for(auto item: matched){
                            result.push_back(path + "/" + item);
                        }
                        if(matched.empty()){
                            result.push_back(curr_word);
                        }
                    }
                    else{
                        result.push_back(curr_word);
                    }
					
					// * seperators
					if(input[i] == '>' && input[i - 1] == '2'){
						result.back() = result.back().substr(0, result.back().size()-1);
						seperators.push_back("2>");
					}else{
						tmp_str = input[i];
						seperators.push_back(tmp_str);
					}


                } else{
					if(input[i] != ' '){
						seperators.back() = input[i];
					}
				}
                // FINISH

            replacing = true;
            curr_word = "";
            is_flag = false;
            continue;
        }
		// check is flag
        if (input[i] == '-' && !double_quotes_opened && curr_word.length() < 1){
            is_flag = true;
        }
        curr_word += input[i];
    }
	seperators.pop_back();


    // Generate result in terms of arguments class
	string redirect_string;
	vector<arguments::Arguments>arguments_vct;
	arguments::Arguments arguments{};
	arguments_vct.push_back(arguments);
	
	for(int i = 0; i < result.size(); i++){

		// Fone handler
		if(i == result.size() - 1 || seperators[i + 1] == "|"){
			if(result[i].size() == 1 && result[i][result[i].size() - 1] == '&'){
				arguments_vct.back().set_fone(true);
				continue;
			}else if(result[i][result[i].size() - 1] == '&'){
				arguments_vct.back().set_fone(true);
				result[i] = result[i].substr(0, result[i].size()-1);
			} else{
				arguments_vct.back().set_fone(false);
			}
		}
		
		// Other handlers (<, 2>, >, |)
		if(seperators[i] == " "){
			arguments_vct.back().add_arg(result[i]);
		}
		else if(seperators[i] == "|")
		{
			arguments::Arguments arguments{};
			arguments_vct.push_back(arguments);
			arguments_vct.back().add_arg(result[i]);
		}
		else{	
			redirect_string = seperators[i] + result[i];
			arguments_vct.back().add_redirect(redirect_string);
			// For debugging too
			// cout<<redirect_string<<endl;
		}
	}

	// For debugging
	// for(auto e: arguments_vct){
	// 	e.print_info();
	// }

	
    return arguments_vct;
}



// void test_args(){
//     string s = "../*.cpp \"spaced arsgument\" ../*.cpp -h M*e";
//     cout<<s<<endl<<"----------"<<endl;
//     vector<string> result = get_args(s);
    
    
//     for(auto item: result){
//         cout<<item<<endl;
//     }
//     cout<<endl;
// }

// void test_wildcard(){
//     vector<string> res = wildcard("*.cpp", "..");
//     for(auto item: res){
//         cout<<item<<endl;
//     }
// }


// int main(){
//     test_args();
//     test_wildcard();
//     return 0;
// }


// cd cmake-build-release/ && cmake ../ -DCMAKE_BUILD_TYPE=Release && make getargs && clear && ./getargs && cd ../
