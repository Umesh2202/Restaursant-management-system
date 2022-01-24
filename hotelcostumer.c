#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sr = 0, order_sr = 0, bill = 0;
struct node
{
    int data;
    int quantity;
    char item[100];
    float price;
    struct node *next;
} *order = NULL;

struct node *push(char item[100], float price, struct node *head1)
{
    struct node *temp = malloc(sizeof(struct node));
    struct node *ptr = head1;
    sr += 1;
    temp->data = sr;
    strcpy(temp->item, item);
    temp->price = price;
    temp->next = NULL;
    if (head1 == NULL)
    {
        head1 = temp;
        return head1;
    }
    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = temp;
    return head1;
}

/////////////////////////////////////////PLACE ORDER///////HAS 2 PARTS///////////////////////////////////////////
//////////////////////////////////////////////////////////ADD NODE TO ORDER START///////////////////////////////////////////////
void create_node(struct node *find_sr, int quantity)
{
    struct node *temp = malloc(sizeof(struct node));
    struct node *ptr1 = order;
    order_sr++;
    temp->data = order_sr;
    temp->quantity = quantity;
    strcpy(temp->item, find_sr->item);
    temp->price = find_sr->price;
    temp->next = NULL;

    if (order == NULL)
    {
        order = temp;
        return;
    }
    else
    {
        while (ptr1->next != NULL)
            ptr1 = ptr1->next;
        ptr1->next = temp;
    }
}
/////////////////////////////////////////////////////////ADD NODE TO ORDER END//////////////////////////////////////////////////////

//////////////////////////////////////////////MAIN PLACE ORDER FUNCTION START////////////////////////////////
struct node *place_order(struct node *head1)
{
    int count = 0, choice, quantity;
    struct node *find_sr;

    find_sr = head1;
    printf("\n                                        Type the order number : ");
    scanf("%d", &choice);

    if (choice > sr + 1 || choice < 1) // check if choice of order is negative or more than the menu amount
        printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Invalid choice !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n");
    else
    {
        printf("                                        Enter the quantity : ");
        scanf("%d", &quantity);
        printf("\n");

        while (find_sr != NULL)
        {
            if (find_sr->data == choice)
            {
                create_node(find_sr, quantity);
            }

            find_sr = find_sr->next;
        }
    }
    return head1;
}
/////////////////////////////////////////////MAIN PLACE ORDER FUNCTION END////////////////////////////////////////////////////////////////

///////////////////////////////////PRINT ORDER START/////////////////////////////////////////////
void displayorder()
{
    struct node *ptr = order;
    printf("                                        Your order is : \n\n");

    while (ptr != NULL)
    {
        printf("                                        %d  %s  Rs%.1f  %d", ptr->data, ptr->item, ptr->price, ptr->quantity);
        printf("\n");
        ptr = ptr->next;
    }
}
/////////////////////////////////////////PRINT ORDER START END////////////////////////////////////////////////////////

/////////////////////////////////DELETE SINGLE ORDER ITEM START////////////////////////////////////////////
void delete_item()
{
    int choice, quantity;
    struct node *ptr = order, *ptr1=order;

    displayorder();
    printf("\n                                        Select order number to delete : ");
    scanf("%d", &choice);
    printf("                                        Enter the quantity to delete : ");
    scanf("%d", &quantity);

    if (order->next == NULL) /////////////////////////////////////////////// to delete item if only one item ordered//////////////
    {
        ptr->quantity = (ptr->quantity) - quantity;
        if (ptr->quantity < 0)
        {
            printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Deletion amount more than ordered quantity !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            return;
        }

        else if (ptr->quantity == 0)
        {
            free(order);
            order = NULL;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    else if (choice == 1) /////////////////////////////////////////////////// to delete first item////////////////////////////////
    {
        ptr->quantity = (ptr->quantity) - quantity;

        if (ptr->quantity < 0) //////////////////if deleting quantity is more than ordered//////////////////////////////
        {
            printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Deletion amount more than ordered quantity !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            return;
        }

        else if (ptr->quantity == 0) ///////////////////////if deleting quantity is equal to ordered////////////////
        {
            ptr1 = ptr1->next;
            while (ptr1 != NULL)
            {
                (ptr1->data)--;
                ptr1 = ptr1->next;
            }
            order = order->next;
            free(ptr);
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    else //////////////////////////////////to delete any other item///////////////////////////////////////////////
    {
        while (ptr->next->data != choice) // to reach a node before sr to be deleted//
            ptr = ptr->next;

        ptr->next->quantity = (ptr->next->quantity) - quantity;

        if (ptr->quantity < 0) //////////////////if deleting quantity is more than ordered//////////////////////////////
        {
            printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Deletion amount more than ordered quantity !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            return;
        }

        else if (ptr->next->quantity == 0) ///////////////////////if deleting quantity is equal to ordered////////////////
        {
            ptr1 = ptr->next->next;
            ptr->next->next = NULL;
            free(ptr->next);
            ptr->next = ptr1;
            while (ptr1 != NULL)
            {
                (ptr1->data)--;
                ptr1 = ptr1->next;
            }
            ptr=NULL;
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    order_sr--;
}
//////////////////////////////////////DELETE SINGLE ORDER ITEM END///////////////////////////////////////////////////////

//////////////////////////////////////////////DELETE ENTIRE ORDER START///////////////////////////////////////////////////////////
void delete_order()
{
    struct node *ptr;
    while (ptr != NULL)
    {
        ptr = order->next;
        order->next = NULL;
        free(order);
        order = ptr;
    }
    order_sr = 0;
}
//////////////////////////////////////////////DELETE ENTIRE ORDER END//////////////////////////////////////////////////////////////

////////////////////////////////////////PRINT MENU START//////////////////////////////////
void displaymenu(struct node *head1)
{
    struct node *ptr = head1;

    while (ptr != NULL)
    {
        printf("%d  %s  Rs%.1f", ptr->data, ptr->item, ptr->price);
        printf("\n");
        ptr = ptr->next;
    }
}
//////////////////////////////////////////PRINT MENU END/////////////////////////////////////////////////

//////////////////////////////////////////BILL CALCULATOR START//////////////////////////////////////////////////
void bill_cal()
{
    struct node *ptr = order;
    bill=0;
    while (ptr != NULL)
    {
        bill += (ptr->price) * (ptr->quantity);
        ptr = ptr->next;
    }
}
//////////////////////////////////////////BILL CALCULATOR END////////////////////////////////////////////////

int main()
{
    struct node *head1 = NULL;
    int choice;
    head1 = push("Poha", 20, head1);
    head1 = push("Idli", 30, head1);
    head1 = push("Medu Wada", 40, head1);

    while (choice != 6)
    {
        printf("\n                                       1.Place order                              \n");
        printf("                                       2.Display order                            \n");
        printf("                                       3.Delete item                              \n");
        printf("                                       4.Delete entire order                      \n");
        printf("                                       5.Diplay bill                              \n");
        printf("                                       6.Exit                                     \n");

        printf("\n                                        Enter choice : ");
        scanf("%d", &choice);
        printf("\n");

        if (choice < 1 || choice > 6)
        {
            printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Invalid choice !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            continue;
        }
        else
        {
            switch (choice)
            {
            case 1:
                displaymenu(head1);
                place_order(head1);
                break;
            case 2:
                displayorder(order);
                break;
            case 3:
                delete_item(order);
                break;
            case 4:
                delete_order(order);
                break;
            case 5:
                bill_cal();
                printf("****************************************************** Your bill : %d *******************************************************\n", bill);
                break;
            case 6:
                exit(1);
            }
        }
    }
}
