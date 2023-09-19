#pragma once
#include "User.h"

class GraphNode {
    public:
        GraphNode(User u);
        friend std::ostream& operator<<(std::ostream& os, const GraphNode& se);
        bool operator==(const GraphNode& other);
        bool operator<(const GraphNode& other);
        bool operator>(const GraphNode& other);

        User* get_value();

        void set_color(std::string new_color);
        std::string get_color();
        
        void set_pred(std::string new_pred);
        std::string get_pred();

        void set_d(int new_d);
        int get_d();
    private:
        User value;
        std::string color, pred;
        int d;
};

std::ostream& operator<<(std::ostream& os, const GraphNode& se);