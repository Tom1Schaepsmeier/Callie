#include <string>

class TTClient {

        std::string mEmail;
        std::string mPassword;

        public:

        /*
            default constructor for the TTClient
        */
        TTClient(std::string email, std::string password);

        /*
            copy constructor 
        */
        TTClient(const TTClient& aTTClient);

        /*
            move constructor
        */
        TTClient(TTClient&& ttClient);

        /*
            copy assignment
        */
        void operator=(const TTClient& ttClient);

        /*
            move assignment
        */
        void operator=(TTClient&& ttClient);

        /*
            login method to TimeTree
        */
        void login();
};
