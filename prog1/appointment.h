#include "vehicle.h"

/*
    @desc:
*/
class Apt
{
public:
    Apt();
    Apt(const Apt &apt);
    Apt(Vehicle &source);
    virtual ~Apt();
    void set_cust_name();
    void set_cust_phone();
    void set_vehicle(Vehicle &source);
    void set_location();
    void set_miles();
    void set_drop_off();
    virtual int calc_fare();
    virtual void display_apt();

protected:
    Vehicle * vehicle;
    char * cust_name;
    char * cust_phone;
    char * location;
    int miles;
    char * drop_off;
};

/*
    @desc:
*/
class Exp : public Apt
{
public:
    Exp();
    Exp(Vehicle &source);
    Exp(const Exp &exp);
    virtual ~Exp();
    int calc_fare();

protected:
    int booking_fee;
    int cancle_fee;
};

/*
    @desc:
*/
class Standard_exp : public Exp
{
public:
    Standard_exp();
    Standard_exp(Vehicle &source);
    virtual ~Standard_exp();
    void display_apt();
    int calc_fare();

protected:
    int standard_fare;

};

/*
    @desc:
*/
class Premium_exp : public Standard_exp
{
public:
    Premium_exp();
    Premium_exp(Vehicle &source);
    virtual ~Premium_exp();
    void display_apt();
    int calc_fare();
    
protected:
    int premium_fare;
    int min_fare;
};

/*
    @desc:
*/
class Group_exp : public Exp
{
public:
    Group_exp();
    Group_exp(Vehicle &source);
    virtual ~Group_exp();
    void display_apt();
    int calc_fare();

protected:
    int max_riders;
    int num_riders;
    int g_fare;
};

class A_node
{

public:
    A_node();
    A_node(const A_node &a_node);
    A_node(Apt &source);
    ~A_node();
    void set_left(A_node * source);
    void set_right(A_node * source);
    A_node *& go_left();
    A_node *& go_right();
    bool if_left() const;
    bool if_right() const;
    void display_node();
protected:
    Apt * apt;
    A_node * left;
    A_node * right;
};

class Apt_manager
{
public:
    Apt_manager();
    ~Apt_manager();
    void new_apt();
    void insert_apt();
    void pop_apt();
protected:
    
};
