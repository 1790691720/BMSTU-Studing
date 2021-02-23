#include <cstdio>
#include <cctype>
#include "Dlink.h"
#include "Symlink.h"
using namespace std;






int main()
{
    SymLink* head;
    SymLink* tail;

    head = new SymLink('\n');
    tail = new SymLink('\n');

    tail->before(head);

    SymLink* maxLink=head;
    SymLink* temp;
    char ch;


    printf("Input string and click enter:\n");

    int maxCh = -1, count = 0, countMax = 0;
    while ((ch = getchar()) != '\n')
    {
        temp = new SymLink(ch);
        tail->before(temp);
        count++;
        if (ch > maxCh)
        {
            maxCh = ch;
            maxLink = temp;
        }
    }






    maxLink->exclusion();

    temp = head;
    for (int i = 0; i < count / 2; i++)
    {
        temp = temp->get_next();
        countMax++;
    }

    temp->after((maxLink));


    
    
    
    head->print();

    if (head->get_next() != maxLink)
         printf("%*c^", countMax, ' ');
    else
         printf("^");





     // Delete this link
     SymLink* q;
     temp = tail;
     while (temp != NULL) {
         q = temp->get_prev();
         temp->exclusion();
         delete temp;
         temp = q;
     }


     return 0;
}
