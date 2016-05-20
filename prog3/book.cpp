#include "book.h"

//*******************************************************************************
//***********************Book Class Functions**********************************
//*******************************************************************************
//char * topic
//P_node * problems
//int num_problems

/*
    @desc:
*/
Book::Book()
{
    topic = NULL;
    problems = NULL;
    num_problems = 0;
}

/*
    @desc:
*/
Book::~Book()
{
    if(topic) delete [] topic;
    topic = NULL;
    remove_all();
    problems = NULL;
    num_problems = 0;
}

/*
    @desc:
*/
Book::Book(const Book &book)
{
    if(book.topic)
    {
        topic = NULL;
        topic = new char[strlen(book.topic) + 1];
        strcpy(topic, book.topic);
    } 
    else topic = NULL;
    num_problems = book.num_problems;
    copy_tree(problems, book.problems);
}

/*
    @desc:
*/
Book & Book::operator += (P_node *& p_node)
{
    if(!p_node) return *this;
    insert_problem(problems, p_node);
    ++num_problems;
    return *this;
}

/*
    @desc:
*/
Book operator + (const Book &book, P_node *& p_node)
{
    if(!p_node) return book;
    Book temp1(book);
    P_node * temp2 = new P_node(*p_node);
    temp1.insert_problem(temp1.problems, temp2);
    return temp1;
}

/*
    @desc:
*/
int Book::copy_tree(P_node *& dest, P_node * source)
{
    if(!source)
    {
        dest = NULL;
        return 0;
    }
    dest = new P_node(*source);
    copy_tree(dest->go_left(), source->go_left());
    copy_tree(dest->go_right(), source->go_right());
    return 1;
}

/*
    @desc:
*/
int Book::create_problem()
{
    int i = 0;
    char * p = new char[500];
    char response = '\0';
    bool c = false;

    cout << "Enter a problem: ";
    cin.get(p, 500, '\n');
    cin.ignore(500, '\n');

    cout << "Enter the problem's importance: ";
    cin >> i;
    cin.ignore(100, '\n');

    cout << "Are you confident with this problem?(y/n): ";
    cin >> response;
    cin.ignore(100, '\n');
    if(response == 'y') c = true;

    P_node * temp = new P_node(i, c, p);
    //TODO
    //insert_problem(problems, temp);
    *this += temp;
    delete [] p;
    ++num_problems;
    return 1;
}

/*
    @desc: TODO automated function for filling a book with given values. 
*/

int Book::auto_populate(char * problem, int importance, bool confidence)
{
    P_node * temp = new P_node(importance, confidence, problem);
    insert_problem(problems, temp);
    ++num_problems;
    return 1;
}

/*
    @desc:
*/
int Book::set_topic(char * source)
{   
    if(!source) return 0;
    if(topic) delete [] topic;
    topic = new char[strlen(source) + 1];
    strcpy(topic, source);
    return 1;
}

/*
    @desc:
*/
int Book::insert_problem(P_node *& root, P_node *& source)
{
    if(!root)
    {
        root = source;
        return 1;
    }
    
    //if the source's importance is greater than or equal to the current
    //problems importance, insert to the right.
    if(!root->compare_importance(*source))
    {
        return insert_problem(root->go_right(), source);
    }

    else
    {
        return insert_problem(root->go_left(), source);
    }
}

/*
    @desc:
*/
void Book::remove_all()
{
    if(problems) remove_all(problems);
    return;
}

/*
    @desc:
*/
void Book::remove_all(P_node *& root)
{   
    if(!root) return;
    remove_all(root->go_left());
    remove_all(root->go_right());
    delete root;
    root = NULL;
    return;
}

/*
    @desc:
*/
void Book::display_all()
{   
    cout << "Problem set: " << topic << endl 
         << "Number of problems: " << num_problems << endl << endl;
    display_all(problems);
    cout << endl << endl;
    return;
}

/*
    @desc:
*/
void Book::display_all(P_node * root)
{
    if(!root) return;
    display_all(root->go_right());
    root->display_problem();
    display_all(root->go_left());
    return;
}

/*
    @desc:
*/
void Book::step_through_problems()
{
    cout << "Problem set: " << topic << endl 
         << "Number of problems: " << num_problems << endl << endl << endl;
    check_problems(problems);
    cout << endl << endl;
    return;
}

/*
    @desc:
*/
void Book::check_problems(P_node *& root)
{
    if(!root) return;
    char response = '\0';
    
    check_problems(root->go_right());
    root->display_problem();
    
    cout << "Do you feel confident with this?(y/n): ";
    cin >> response;
    cin.ignore(100, '\n');
    
    if(response == 'y') root->set_confidence(true);
    else root->set_confidence(false);

    cout << endl;
    
    check_problems(root->go_left());
    return;
}

//*******************************************************************************
//***********************B_node Class Functions**********************************
//*******************************************************************************
//B_node * next

/*
    @desc:
*/
B_node::B_node()
{
    next = NULL;
}

/*
    @desc:
*/
B_node::B_node(const B_node &b_node) : Book(b_node)
{
    next = NULL;
}

/*
    @desc:
*/
B_node::~B_node()
{
    next = NULL;
}

/*
    @desc:
*/
bool B_node::if_next()
{
    if(next) return true;
    return false;
}

/*
    @desc:
*/
void B_node::set_next(B_node * source)
{
   next = source;
   return;
}

/*
    @desc:
*/
B_node *& B_node::go_next()
{
    return next;
}

