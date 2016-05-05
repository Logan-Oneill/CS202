#include "deck.h"

//*********************DECK CLASS FUNCTIONS*************************************
//Card *** the_deck
//Card *** the_board

/*
    @desc:
*/
Deck::Deck()
{
    the_deck = new Card * [52];
    int index = 0;

    for(int i = 0; i < 13; ++i)
    {
        index = i + 1;
        the_deck[i] = new Card(1, index);
    } 
    
    for(int i = 13; i < 26; ++i)
    {   
        index = i + 1;
        index = index % 13;
        
        if(index == 0)
        {
            the_deck[i] = new Card(2, 13);
        }

        else
        {
            the_deck[i] = new Card(2, index);
        }
    } 
    
    for(int i = 26; i < 39; ++i)
    {
        index = i + 1;
        index = index % 13;
        
        if(index == 0)
        {
            the_deck[i] = new Card(3, 13);
        }

        else
        {
            the_deck[i] = new Card(3, index);
        }
    } 
    
    for(int i = 39; i < 52; ++i)
    {
        index = i + 1;
        index = index % 13;
        
        if(index == 0)
        {
            the_deck[i] = new Card(4, 13);
        }

        else
        {
            the_deck[i] = new Card(4, index);
        }
    } 
}    
/*
    @desc:
*/

Deck::~Deck()
{
    for(int i = 0; i < 53; ++i)
    {
        delete the_deck[i];
    }

    delete [] the_deck;
}       
/*
    @desc:
*/

void Deck::shuffle()
{
    srand(time(NULL));
    
    int index_to_swap = 0;
    
    for(int j = 0; j < 3; ++j)
    {
        for(int i = 0; i < 52; ++i)
        {
            index_to_swap = rand() % 52;
            Card * temp = the_deck[i];
            the_deck[i] = the_deck[index_to_swap];
            the_deck[index_to_swap] = temp;
        }
    }

    return;
}   
/*
    @desc:
*/
    
void Deck::display_deck()
{
    for(int i = 0; i < 52; ++i)
    {
        //TODO
        the_deck[i]->set_hidden(false);
        cout << i << "_";
        //TODO
        the_deck[i]->display_card();
    }

    return;
}    
/*
    @desc:
*/
    
void Deck::display_board()
{

}


//******************************************************************************

//**********************S_node Functions****************************************
//S_node * next
//S_node * prev
//Card * card

S_node::S_node()
{
    next = NULL;
    prev = NULL;
    card = NULL;
}

S_node::S_node(const Card &aCard)
{
    next = NULL;
    prev = NULL;
    card = NULL;
    card = new Card(aCard);
}

S_node::~S_node()
{
    next = NULL;
    prev = NULL;
    if(card) delete card;
    card = NULL;
}

S_node *& S_node::go_next()
{
    return next;
}

S_node *& S_node::go_prev()
{
    return prev;
}

bool S_node::if_next() const
{
    if(next) return true;
    return false;
}

bool S_node::if_prev() const
{
    if(prev) return true;
    return false;
}

void S_node::set_next(S_node * source)
{
    if(source) next = source;
    else next = NULL;
    return;
}

void S_node::set_prev(S_node * source)
{
    if(source) prev = source;
    else prev = NULL;
    return;
}

void S_node::display_node()
{
    card->display_card();
    return;
}


void S_node::set_status(bool status)
{
    card->set_hidden(status);
    return;
}

bool S_node::compare_nodes(S_node * source)
{
    return card->compare_cards(*source->card);
}

bool S_node::our_cards_the_same(S_node * source)
{
    return card->are_the_same(*source->card);
}
//******************************************************************************


//*************************Solitaire class functions****************************
//S_node ** board
//S_node *** display_board
Solitaire::Solitaire()
{
    //Two different boards are used, one for the data structure keeping track
    //of the cards in a specified order, and another for displaying. First we
    //initialize the board data structure
    board = new S_node * [13];
    for(int i = 0; i < 13; ++i)
    {
        board[i] = NULL;
    }
    deal_cards();
    
    //Then we initialize the display board and null out all pointers.
    display_board = new S_node ** [13];
    
    for(int i = 0; i < 13; ++i)
    {
        display_board[i] = new S_node * [20];
    }
    
    clear_display_board();
}

Solitaire::~Solitaire()
{

}

void Solitaire::initialize_board()
{
    
}

//TODO
void Solitaire::insert_card(int i, S_node * &source)
{
    if(!board[i]) 
    {   
        board[i] = source; 
        return;
    }

    source->set_next(board[i]);
    board[i]->set_prev(source);
    board[i] = source;
    return;
}
//TODO
void Solitaire::deal_cards()
{
    int index = 0;
    
    for(int i = 0; i < 7; ++i)
    {
        for(int j = 0; j < i + 1; ++j)
        {
            S_node * temp = new S_node(*the_deck[index]);
            insert_card(i, temp);
            ++index;
        }
    }

    for(index; index < 52; ++index)
    {
        S_node * temp = new S_node(*the_deck[index]);
        insert_card(11, temp);
    }

    return;
}
//TODO purely for testing

void Solitaire::display_garbage_wrapper()
{
    for(int i = 0; i < 7; ++i)
    {
        display_garbage(board[i]);
        cout << endl << endl;
    }

    display_garbage(board[11]);

    return;
}
//TODO purely for testing
void Solitaire::display_garbage(S_node * head)
{
    if(!head) return;
    head->display_node();
    display_garbage(head->go_next());
    return;
}

void Solitaire::clear_display_board()
{
    for(int i = 0; i < 13; ++i)
    {
        for(int j = 0; j < 20; ++j)
        {
            display_board[i][j] = NULL;
        }
    }

    return;
}

void Solitaire::send_to_d_board_wrapper()
{
    for(int i = 0; i < 7; ++i)
    {
        send_to_d_board(i, 0, board[i]); 
    }
    
    for(int i = 7; i < 13; ++i)
    {
        if(board[i])
        {
            display_board[i][0] = board[i];
        }
    }

    return;
}

void Solitaire::send_to_d_board(int i, int j, S_node * head)
{
    if(!head)
    {
        return;
    }

    display_board[i][j] = head;
    //TODO possible erro
    ++j;
    send_to_d_board(i, j, head->go_next());
    return;
}

void Solitaire::d_board()
{
    int index = 0;
    cout << "******************************************************************"
         << "**********************************************" << endl;
    cout << "***********************************SOLITAIRE BOARD****************"
         << "**********************************************" << endl;
    cout << "******************************************************************"
         << "**********************************************" << endl;
    cout << "T: 1    " << "T: 2    " << "T: 3    " << "T: 4    " << "T: 5    " 
         << "T: 6    " << "T: 7    " << "H aces  " << "D Aces  " << "C Aces  "
         << "S Aces  " << "Talon   " << "Hand   " << endl;
    
    for(int j = 0; j < 20; ++j)
    {
        for(int i = 0; i < 13; ++i)
        {
            if(!display_board[i][j])
            {
                cout << "        ";
            }
            if(display_board[i][j])
            {
                display_board[i][j]->display_node();
                
                cout << "     ";
            }

        }
        cout << endl;
    }
    
    /*
    if(display_board[7][0])
    {
        cout << "here" << endl;
        display_board[12][0]->display_node();
        cout << "here" << endl;
        cout << endl;
    }
    */

    return;
}

/*
bool Solitaire::compare_cards(S_node * dest, S_node * source)
{
    return dest->compare_nodes(source);
}
*/

void::Solitaire::play_game()
{
    cout << endl << endl;
    cout << "Welcome screen." << endl;
    cout << "Rules: for suits 1 is hearts, 2 is diamonds, 3 is clubs, 4 is"
         << " spades. Aces are 1, 2 through 10 and simply 2 through 10,"
         << endl << "Jacks are 11, queens are 12, Kings are 13.";
    cout << endl << endl;
    send_to_d_board_wrapper();
    d_board();
    
    cout << "to make a move input the table index, the suite, and the card's"
         << " value.";
    cout << "make move: " << endl;
    cout << "move to: " << endl;
    int index = 0;
    int s = 0;
    int v = 0;
}

S_node * Solitaire::find_node_wrapper(int index, int s, int v)
{
    Card aCard(s, v);
    return find_node(board[index], aCard);
}

S_node * find_node(S_node * head, Card source)
{
    if(!head) return NULL;

    //TODO
    //CONTINUE HERE!!!!!!!!
}

//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
