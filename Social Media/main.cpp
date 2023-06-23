// This can be improve we can include check in Create Post for checking the user is logged or not
// and can have logged state in User

#include<bits/stdc++.h>
using namespace std;

class User {
private:
    string username;
    string password;

public:
    User(const string& username, const string& password)
        : username(username), password(password) {}

    std::string getUsername() const {
        return username;
    }

    bool authenticate(const std::string& password) const {
        return this->password == password;
    }
};

class Post {
private:
    string content;
    User author;

public:
    Post(const string& content, const User& author)
        : content(content), author(author) {}

    string getContent() const {
        return content;
    }

    User getAuthor() const {
        return author;
    }
};

class SocialMediaApp {
private:
    vector<User> users;
    vector<Post> posts;

public:
    bool registerUser(const string& username, const string& password) {
        for (const User& user : users) {
            if (user.getUsername() == username) {
                std::cout << "Username already exists. Please choose a different username." << std::endl;
                return false;
            }
        }

        users.push_back(User(username, password));
        std::cout << "User registered successfully." << std::endl;
        return true;
    }

    bool loginUser(const string& username, const string& password) {
        for (const User& user : users) {
            if (user.getUsername() == username) {
                if (user.authenticate(password)) {
                    cout << "Login successful. Welcome, " << username << "!" << endl;
                    return true;
                } else {
                    cout << "Incorrect password. Please try again." << endl;
                    return false;
                }
            }
        }

        cout << "User not found. Please register an account." << std::endl;
        return false;
    }

    void createPost(const std::string& content, const User& author) {
        posts.push_back(Post(content, author));
        cout << "Post created successfully." << std::endl;
    }
};

int main() {
    SocialMediaApp app;
    app.registerUser("Harsh", "pwd");
    app.loginUser("john_doe", "password123");
    app.createPost("Hello, world!", User("john_doe", "password123"));

    return 0;
}
