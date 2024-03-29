#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
using namespace std;

/*
    @desc: A vehicle is an object comprised of a make, a model and a license.
*/
class Vehicle
{

public:
    Vehicle();
    Vehicle(const Vehicle &vehicle);
    ~Vehicle();
    void set_make(char * source);
    void set_model(char * source);
    void set_license(char * source);
    void display();
protected:
    char * make;
    char * model;
    char * license;
};

/*
    @desc: A vehicle node IS A vehicle plus the ability to link to other
        vehicles, allowing for the developement of different list-type data 
        structures.
*/
class V_node: public Vehicle
{

public:
    V_node();
    V_node(const V_node &v_node);
    ~V_node();
    void set_next(V_node * source);
    V_node *& go_next();
    bool if_next() const;
    bool compare_make(char * source);
    bool compare_model(char * source);
protected:
    V_node * next;
};

/*
    @desc: is a class managing a array of three circular linked lists. It will
        read in data from an external data file, create new vehicle nodes with 
        this data, 
*/
class V_manager
{

public:
    V_manager();
    ~V_manager();
    void insert_vehicle(char * index, V_node *& source);
    void display_all();
    void display_standard();
    void display_premium();
    void display_group();
    void remove_vehicle(char * v_make, char * v_model);
    int remove_helper(V_node * &head, V_node * &current, char * v_make, 
                      char * v_model);
    void remove_all_helper(V_node * &head);
    void remove_all();
    Vehicle * get_vehicle(int i, char * v_make, char * v_model);
    Vehicle * get_vehicle_helper(V_node * head, char * v_make, char * v_model);
            
protected:
    void file_read();
    V_node ** table;
    int MAX;
};
