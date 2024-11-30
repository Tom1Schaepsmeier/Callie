#include <string>

#include "TTClient.h"

TTClient::TTClient(std::string email, std::string password) : mEmail(email), 
                                                              mPassword(password) 
    {}

TTClient::TTClient(const TTClient& aTTClient) : mEmail(aTTClient.mEmail),
                                                mPassword(aTTClient.mPassword) 
    {}

TTClient::TTClient(TTClient&& aTTClient) : mEmail(std::move(aTTClient.mEmail)),
                                           mPassword(std::move(aTTClient.mPassword)) 
    {}

void TTClient::operator=(const TTClient& aTTClient) {
    mEmail = aTTClient.mEmail;
    mPassword = aTTClient.mPassword;
}

void TTClient::operator=(TTClient&& aTTClient) {
    mEmail = std::move(aTTClient.mEmail);
    mPassword = std::move(aTTClient.mPassword);
}

void TTClient::login() {
    
}
