#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// �Լ� ����
void MainMenu(void);
void CustomerMenu(void);
void SearchUsingID(void);
void ItemInfo(int);
void addToCart(int);
void removeFromCart(void);
void SelectCartMenu(void);
void ShowCartList(void);
int CartSum(void);
void CheckOut(void);
void AdminLogin(void);
void AdminMenu(void);
void addItem(void);
void removeItem(void);
void flushInputBuffer(void);
void removeInputEnter(char* str);
void ShowEveryItem(void);
void ShowNewItem(void);
void LoadItemsFromFile(void);
void SaveItemsToFile(void);
void CreateItemsFile(void);
void LoadCartListFromFile(void);
void SaveCartListToFile(void);
void CreateCartListFile(void);
void ResetCartList(void);

// ��ǰ ����ü ����
struct item {
    char item_name[30];
    char item_desc[200];
    int item_number;
    int item_price;
};
typedef struct item Item;
// ��ٱ��� ����ü ����
struct cart {
    char cart_item_name[30];
    int cart_id;
    int cart_number;
    int cart_item_price;
};
typedef struct cart Cart;

//���� ���� ����
Item items[100];
int item_count = 0;
Cart cartlist[80];
int cart_count = 0;
int searchedItemID = 0;

int main(void) {
    LoadItemsFromFile(); // ���α׷� ���� �� ���Ͽ��� ��ǰ ������ �ҷ���
    LoadCartListFromFile(); // ���α׷� ���� �� ����īƮ�� ��ǰ ������ �ҷ���

    int input_menu;

    printf(" #######  ##    ## ##       #### ##    ## ########     ######  ##     ##  #######  ########  #### ##    ##  ######   \n##     ## ###   ## ##        ##  ###   ## ##          ##    ## ##     ## ##     ## ##     ##  ##  ###   ## ##    ##  \n##     ## ####  ## ##        ##  ####  ## ##          ##       ##     ## ##     ## ##     ##  ##  ####  ## ##        \n##     ## ## ## ## ##        ##  ## ## ## ######       ######  ######### ##     ## ########   ##  ## ## ## ##   #### \n##     ## ##  #### ##        ##  ##  #### ##                ## ##     ## ##     ## ##         ##  ##  #### ##    ##  \n##     ## ##   ### ##        ##  ##   ### ##          ##    ## ##     ## ##     ## ##         ##  ##   ### ##    ##  \n #######  ##    ## ######## #### ##    ## ########     ######  ##     ##  #######  ##        #### ##    ##  ######   \n");

    while (1) {
        MainMenu();
        if (scanf("%d", &input_menu) != 1) {
            flushInputBuffer();
            printf("�߸��� �Է��Դϴ�. ���ڸ� �Է��Ͻʽÿ�.\n");
            continue;
        }

        switch (input_menu) {
        case 1:
            CustomerMenu();
            break;
        case 2:
            AdminLogin();
            break;
        case 3:
            printf("������ �����մϴ�.\n");
            exit();
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��Ͻʽÿ�.\n");
            break;
        }
    }
    return 0;
}

void MainMenu(void) {
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("1. ��ǰ ���� \n");
    printf("2. ������ �α��� \n");
    printf("3. ���� \n");
    printf("\n");
    printf(">> ");
}

void CustomerMenu(void) {
    LoadItemsFromFile();
    if (item_count == 0) {
        printf("���� ��ϵ� �������� �����ϴ�.\n");
        return;
    }

    while (1) {
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        ShowNewItem(); // �ֱ� �߰��� ��ǰ�� ������
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("[1] ��ǰ Ž���ϱ� [2] ��ٱ��� Ȯ�� [3] ó������ \n\n>> ");

        int MenuSelect;

        if (scanf("%d", &MenuSelect) != 1) {
            flushInputBuffer(); // �Է� ���� �÷���
            printf("�߸��� �Է��Դϴ�. ���ڸ� �Է��ϼ���.\n");
            continue;
        }

        switch (MenuSelect) {
        case 1:
            SearchUsingID();
            break;
        case 2:
            SelectCartMenu();
            break;
        case 3:
            return;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            break;
        }
    }
}

// ��ǰ�� ID(item_number)�� ���� ��ǰ �˻�
void SearchUsingID(void) {
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    ShowEveryItem();
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");

    int item_ID;

    printf("��ǰ�� ID�� �Է��Ͻʽÿ�. \n\n>> ");

    scanf("%d", &item_ID);

    if (item_ID >= item_count || 0 > item_ID)
    {
        printf("��ϵ��� ���� ��ǰ�Դϴ�\n");
        return;
    }

    searchedItemID = item_ID;
    ItemInfo(searchedItemID);
}

// ��ǰ �ڼ��� ����
void ItemInfo(int searchedItem) {
    int MenuSelect;
    
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("ID: %d   ��ǰ��: %s \n", items[searchedItem].item_number, items[searchedItem].item_name);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("%s \n", items[searchedItem].item_desc);
    printf("\n");
    printf("����: %d�� \n", items[searchedItem].item_price);

    while (1) {
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("[1] ��ٱ��Ͽ� �ֱ� [2] �������� \n\n>> ");

        if (scanf("%d", &MenuSelect) != 1) {
            flushInputBuffer();
            printf("�߸��� �Է��Դϴ�. ���ڸ� �Է��ϼ���.\n");
            continue;
        }

        switch (MenuSelect) {
        case 1:
            addToCart(searchedItem);
            break;
        case 2:
            return;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            break;
        }
    }
}

// ��ٱ��Ͽ� ��ǰ �߰�
void addToCart(int item_id) {
    if (cart_count >= 80) {
        printf("��ٱ��ϰ� ���� á���ϴ�.\n");
        return;
    }

    cartlist[cart_count].cart_id = cart_count;
    cartlist[cart_count].cart_number = items[item_id].item_number;
    strcpy(cartlist[cart_count].cart_item_name, items[item_id].item_name);
    cartlist[cart_count].cart_item_price = items[item_id].item_price;

    cart_count++;
    SaveCartListToFile();

    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("��ٱ��Ͽ� �߰��Ǿ����ϴ�! (%d/80) \n", cart_count);
    
}

// ��ٱ��Ͽ��� ��ǰ ����
void removeFromCart(void) {
    int removeCID;
    printf("������ ��ǰ�� **CID** �Է� >> ");

    if (scanf("%d", &removeCID) != 1) {
        flushInputBuffer();
        printf("�߸��� �Է��Դϴ�. ������ �Է��Ͻʽÿ�.\n");
        return;
    }

    if (removeCID < 0 || removeCID >= cart_count) {
        printf("�߸��� ID�Դϴ�. \n");
        return;
    }

    for (int i = removeCID; i < cart_count - 1; i++) {
        cartlist[i] = cartlist[i + 1];
        cartlist[i].cart_id = i;
    }

    cart_count--;

    printf("��ǰ�� ��ٱ��Ͽ��� ���ŵǾ����ϴ�.\n");
    SaveCartListToFile(); // ������ ���� �� ���Ͽ� ����
}



void SelectCartMenu(void) {
    LoadCartListFromFile();
    SaveCartListToFile();

    if (cart_count == 0) {
        printf("��ٱ��Ͽ� ��� ��ǰ�� �����ϴ�.\n");
        return;
    }

    int MenuSelect;

    while (1) {
        ShowCartList();
        if (scanf("%d", &MenuSelect) != 1) {
            flushInputBuffer();
            printf("�߸��� �Է��Դϴ�. ���ڸ� �Է��Ͻʽÿ�.\n");
            continue;
        }

        switch (MenuSelect) {
        case 1:
            CheckOut();
            break;
        case 2:
            removeFromCart();
            if (cart_count <= 0) { return; } // ��ٱ��Ͽ� ��ǰ�� �������� ���� ���, customer_Menu�� ���ư���
            break;
        case 3:
            return;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��Ͻʽÿ�.\n");
            break;
        }
    }
}

// ��ٱ��� ����
void ShowCartList(void) {
    LoadCartListFromFile();
    SaveCartListToFile();

    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("��ٱ��� ��ǰ ��: (%d/80) \n", cart_count);
    printf("%-3s | %-30s | %-10s | %-2s \n", "CID", "��ǰ��", "����", "ID");
    for (int i = 0; i < cart_count; i++) {
        printf("%-3d | %-30s | %-10d | %-2d \n",
            cartlist[i].cart_id,
            cartlist[i].cart_item_name,
            cartlist[i].cart_item_price,
            cartlist[i].cart_number
        );
    }

    int sum = CartSum();

    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("�հ�: %d\n", sum);
    printf("[1] üũ�ƿ� �ϱ� [2] ��ǰ �����ϱ� [3] ��� �����ϱ� \n\n>> ");
    return;
}

int CartSum(void) {
    int sum = 0;
    for (int i = 0; i < cart_count; i++) {
        sum = cartlist[i].cart_item_price + sum;
    }
    return sum;
}


// üũ�ƿ� �� ��ٱ����� ������ ����
void CheckOut(void) {
    int sum = CartSum();
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("������ �ּż� �����մϴ�! ����� ��ǰ�� �� ��۵� �����Դϴ�. \n");
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("���� ���� \n");
    printf("%-3s | %-30s | %-10s | %-2s \n", "CID", "��ǰ��", "����", "ID");
    for (int i = 0; i < cart_count; i++) {
        printf("%-3d | %-30s | %-10d | %-2d \n",
            cartlist[i].cart_id,
            cartlist[i].cart_item_name,
            cartlist[i].cart_item_price,
            cartlist[i].cart_number
        );
    }
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("���հ�: %d�� \n", sum);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");

    ResetCartList();

    int MenuSelect;
    while (1) {
        printf("[1] ó������ [2] ���� ���� \n\n>> ");

        if (scanf("%d", &MenuSelect) != 1) {
            flushInputBuffer();
            printf("�߸��� �Է��Դϴ�. ���ڸ� �Է��Ͻʽÿ�.\n");
            continue;
        }

        switch (MenuSelect) {
        case 1:
            main();
            break;
        case 2:
            printf("������ �����մϴ�.");
            exit();
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��Ͻʽÿ�.\n");
            break;
        }
    }
}

// ������ ���� ����

// ���� �α���
void AdminLogin(void) {
    char admin_id[20];
    char admin_password[20];
    flushInputBuffer();
    printf("ID: ");
    fgets(admin_id, sizeof(admin_id), stdin);
    removeInputEnter(admin_id);

    printf("PW: ");
    fgets(admin_password, sizeof(admin_password), stdin);
    removeInputEnter(admin_password);

    if (strcmp(admin_id, "admin") == 0 && strcmp(admin_password, "admin123") == 0) {
        AdminMenu();
    }
    else {
        printf("ID �Ǵ� ��й�ȣ�� Ʋ�Ƚ��ϴ�.\n");
    }
}

void AdminMenu(void) {
    int admin_menu = 0;
    printf("\n   ###    ########  ##     ## #### ##    ## \n  ## ##   ##     ## ###   ###  ##  ###   ## \n ##   ##  ##     ## #### ####  ##  ####  ## \n##     ## ##     ## ## ### ##  ##  ## ## ## \n######### ##     ## ##     ##  ##  ##  #### \n##     ## ##     ## ##     ##  ##  ##   ### \n##     ## ########  ##     ## #### ##    ## \n");
    while (1) {
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("1. ��ǰ �߰� \n");
        printf("2. ��ǰ ���� \n");
        printf("3. �α׾ƿ� \n");
        printf("\n>> ");

        if (scanf("%d", &admin_menu) != 1) {
            flushInputBuffer();
            printf("�߸��� �Է��Դϴ�. ���ڸ� �Է��ϼ���.\n");
            continue;
        }

        switch (admin_menu) {
        case 1:
            addItem();
            break;
        case 2:
            removeItem();
            break;
        case 3:
            printf("�α׾ƿ� �մϴ�.\n");
            return;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            break;
        }
    }
}

// ��ǰ �߰�(����)
void addItem(void) {
    if (item_count >= 100) {
        printf("�������� �� �̻� �߰��� �� �����ϴ�.\n");
        return;
    }

    items[item_count].item_number = item_count;

    printf("��ǰ �� (%d/100) \n", item_count);
    flushInputBuffer();
    printf("������ �̸� �Է� (���� ����) >> ");
    fgets(items[item_count].item_name, sizeof(items[item_count].item_name), stdin);
    removeInputEnter(items[item_count].item_name);

    printf("������ ���� �Է� (���� ����) >> ");
    fgets(items[item_count].item_desc, sizeof(items[item_count].item_desc), stdin);
    removeInputEnter(items[item_count].item_desc);

    printf("������ ����(����) �Է� >> ");
    if (scanf("%d", &items[item_count].item_price) != 1) {
        flushInputBuffer();
        printf("�߸��� �Է��Դϴ�. ������ �Է��ϼ���.\n");
        return;
    }

    printf("��ǰ �߰� - - - - - -\n");
    printf("��ǰ�� ID [%d] | ��ǰ�� : [%s] | ���� : [%s] | ���� : [%d] \n",
        items[item_count].item_number,
        items[item_count].item_name,
        items[item_count].item_desc,
        items[item_count].item_price);

    item_count++;
    SaveItemsToFile(); // ������ �߰� �� ���Ͽ� ����
}

// ������ ��ǰ ����
void removeItem(void) {
    if (item_count == 0) {
        printf("��ǰ�� �������� �ʽ��ϴ�.\n");
        return;
    }

    int item_number;
    ShowEveryItem();
    printf("������ ��ǰ�� ID �Է� >> ");

    if (scanf("%d", &item_number) != 1) {
        flushInputBuffer();
        printf("�߸��� �Է��Դϴ�. ������ �Է��Ͻʽÿ�.\n");
        return;
    }

    if (item_number < 0 || item_number >= item_count) {
        printf("�߸��� ID�Դϴ�. \n");
        return;
    }

    for (int i = item_number; i < item_count - 1; i++) {
        items[i] = items[i + 1];
        items[i].item_number = i;
    }

    item_count--;

    printf("��ǰ ���� �Ϸ�.\n");
    SaveItemsToFile(); // ������ ���� �� ���Ͽ� ����
}

void flushInputBuffer(void) {
    while (getchar() != '\n');
}

void removeInputEnter(char* str) {
    int i = 0;
    while (str[i] != '\n' && str[i] != '\0')
        i++;
    str[i] = '\0';
}

// �� �� �ʿ������� �տ� �߰����� ���� �͵�

// ��ǰ ��� ��ü �����ֱ�
void ShowEveryItem(void) {
    LoadItemsFromFile();
    SaveItemsToFile();
    printf("��ǰ �� (%d/100) \n", item_count);
    printf("%-2s | %-30s | %-10s \n", "ID", "��ǰ��", "����");
    for (int i = 0; i < item_count; i++) {
        printf("%-2d | %-30s | %-10d \n",
            items[i].item_number,
            items[i].item_name,
            items[i].item_price
        );
    }
}

// �ֱٿ� ���� 5���� ������(ID�� ���� ������ 5��) ǥ��
void ShowNewItem(void) {
    LoadItemsFromFile();
    SaveItemsToFile();
    printf("�ֱٿ� ���� ��ǰ \n");
    int recentitem = (item_count <= 5) ? 0 : item_count - 5; // item_count�� 5 ���� �۰ų� ������ �ֱٿ� �߰��� ������ ��� ǥ��
    printf("%-2s | %-30s | %-10s \n", "ID", "��ǰ��", "����");
    for (int i = recentitem; i < item_count; i++) {
        printf("%-2d | %-30s | %-10d \n",
            items[i].item_number,
            items[i].item_name,
            items[i].item_price
        );
    }
}

// ���� �����


// items.txt���� item�� �� ��������
void LoadItemsFromFile(void) {
    FILE* file = fopen("items.txt", "r");
    if (file == NULL) {
        printf("items ������ �������� �ʽ��ϴ�. ������ �����մϴ�.\n");
        CreateItemsFile();
        return;
    }

    item_count = 0;
    while (fscanf(file, "%d %s %d %[^\n]s", &items[item_count].item_number, items[item_count].item_name, &items[item_count].item_price, items[item_count].item_desc) == 4) {
        item_count++;
    }

    fclose(file);
}

// items.txt�� item �� �����ϱ�
void SaveItemsToFile(void) {
    FILE* file = fopen("items.txt", "w");
    if (file == NULL) {
        printf("items ������ �������� �ʽ��ϴ�. ������ �����մϴ�.\n");
        CreateItemsFile();
        return;
    }

    for (int i = 0; i < item_count; i++) {
        fprintf(file, "%d %s %d %s\n", items[i].item_number, items[i].item_name, items[i].item_price, items[i].item_desc);
    }

    fclose(file);
}

// items.txt ����
void CreateItemsFile(void) {
    FILE* file = fopen("items.txt", "w+");
    fclose(file);
    return;
}

// CartList.txt���� ��ٱ��� �� ��������
void LoadCartListFromFile(void) {
    FILE* file = fopen("cartlist.txt", "r");
    if (file == NULL) {
        printf("cartlist ������ �������� �ʽ��ϴ�. ������ �����մϴ�.\n");
        CreateCartListFile();
        return;
    }

    cart_count = 0;
    while (fscanf(file, "%d %s %d %d", &cartlist[cart_count].cart_id, cartlist[cart_count].cart_item_name, &cartlist[cart_count].cart_item_price, &cartlist[cart_count].cart_number) == 4) {
        cart_count++;
    }

    fclose(file);
}

// CartList.txt�� ��ٱ��� �� ����
void SaveCartListToFile(void) {
    FILE* file = fopen("cartlist.txt", "w");
    if (file == NULL) {
        printf("cartlist ������ �������� �ʽ��ϴ�. ������ �����մϴ�.\n");
        CreateCartListFile();
        return;
    }

    for (int i = 0; i < cart_count; i++) {
        fprintf(file, "%d %s %d %d\n", cartlist[i].cart_id, cartlist[i].cart_item_name, cartlist[i].cart_item_price, cartlist[i].cart_number);
    }

    fclose(file);
}

// CartList.txt ����
void CreateCartListFile(void) {
    FILE* file = fopen("cartlist.txt", "w+");
    fclose(file);
    return;
}

// ��ٱ��� ����(CartList.txt ���� �� �����)
void ResetCartList(void) {
    remove(cartlist);
    CreateCartListFile();
}
