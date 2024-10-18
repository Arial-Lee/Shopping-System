#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// 함수 선언
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

// 상품 구조체 정의
struct item {
    char item_name[30];
    char item_desc[200];
    int item_number;
    int item_price;
};
typedef struct item Item;
// 장바구니 구조체 정의
struct cart {
    char cart_item_name[30];
    int cart_id;
    int cart_number;
    int cart_item_price;
};
typedef struct cart Cart;

//전역 변수 선언
Item items[100];
int item_count = 0;
Cart cartlist[80];
int cart_count = 0;
int searchedItemID = 0;

int main(void) {
    LoadItemsFromFile(); // 프로그램 시작 시 파일에서 상품 정보를 불러옴
    LoadCartListFromFile(); // 프로그램 시작 시 쇼핑카트의 상품 정보를 불러옴

    int input_menu;

    printf(" #######  ##    ## ##       #### ##    ## ########     ######  ##     ##  #######  ########  #### ##    ##  ######   \n##     ## ###   ## ##        ##  ###   ## ##          ##    ## ##     ## ##     ## ##     ##  ##  ###   ## ##    ##  \n##     ## ####  ## ##        ##  ####  ## ##          ##       ##     ## ##     ## ##     ##  ##  ####  ## ##        \n##     ## ## ## ## ##        ##  ## ## ## ######       ######  ######### ##     ## ########   ##  ## ## ## ##   #### \n##     ## ##  #### ##        ##  ##  #### ##                ## ##     ## ##     ## ##         ##  ##  #### ##    ##  \n##     ## ##   ### ##        ##  ##   ### ##          ##    ## ##     ## ##     ## ##         ##  ##   ### ##    ##  \n #######  ##    ## ######## #### ##    ## ########     ######  ##     ##  #######  ##        #### ##    ##  ######   \n");

    while (1) {
        MainMenu();
        if (scanf("%d", &input_menu) != 1) {
            flushInputBuffer();
            printf("잘못된 입력입니다. 숫자를 입력하십시오.\n");
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
            printf("쇼핑을 종료합니다.\n");
            exit();
        default:
            printf("잘못된 선택입니다. 다시 시도하십시오.\n");
            break;
        }
    }
    return 0;
}

void MainMenu(void) {
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("1. 상품 구매 \n");
    printf("2. 관리자 로그인 \n");
    printf("3. 종료 \n");
    printf("\n");
    printf(">> ");
}

void CustomerMenu(void) {
    LoadItemsFromFile();
    if (item_count == 0) {
        printf("현재 등록된 아이템이 없습니다.\n");
        return;
    }

    while (1) {
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        ShowNewItem(); // 최근 추가된 상품을 보여줌
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("[1] 상품 탐색하기 [2] 장바구니 확인 [3] 처음으로 \n\n>> ");

        int MenuSelect;

        if (scanf("%d", &MenuSelect) != 1) {
            flushInputBuffer(); // 입력 버퍼 플러시
            printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
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
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            break;
        }
    }
}

// 상품의 ID(item_number)를 통한 상품 검색
void SearchUsingID(void) {
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    ShowEveryItem();
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");

    int item_ID;

    printf("상품의 ID를 입력하십시오. \n\n>> ");

    scanf("%d", &item_ID);

    if (item_ID >= item_count || 0 > item_ID)
    {
        printf("등록되지 않은 상품입니다\n");
        return;
    }

    searchedItemID = item_ID;
    ItemInfo(searchedItemID);
}

// 상품 자세한 설명
void ItemInfo(int searchedItem) {
    int MenuSelect;
    
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("ID: %d   상품명: %s \n", items[searchedItem].item_number, items[searchedItem].item_name);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("%s \n", items[searchedItem].item_desc);
    printf("\n");
    printf("가격: %d원 \n", items[searchedItem].item_price);

    while (1) {
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("[1] 장바구니에 넣기 [2] 이전으로 \n\n>> ");

        if (scanf("%d", &MenuSelect) != 1) {
            flushInputBuffer();
            printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
            continue;
        }

        switch (MenuSelect) {
        case 1:
            addToCart(searchedItem);
            break;
        case 2:
            return;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            break;
        }
    }
}

// 장바구니에 상품 추가
void addToCart(int item_id) {
    if (cart_count >= 80) {
        printf("장바구니가 가득 찼습니다.\n");
        return;
    }

    cartlist[cart_count].cart_id = cart_count;
    cartlist[cart_count].cart_number = items[item_id].item_number;
    strcpy(cartlist[cart_count].cart_item_name, items[item_id].item_name);
    cartlist[cart_count].cart_item_price = items[item_id].item_price;

    cart_count++;
    SaveCartListToFile();

    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("장바구니에 추가되었습니다! (%d/80) \n", cart_count);
    
}

// 장바구니에서 상품 제거
void removeFromCart(void) {
    int removeCID;
    printf("제거할 상품의 **CID** 입력 >> ");

    if (scanf("%d", &removeCID) != 1) {
        flushInputBuffer();
        printf("잘못된 입력입니다. 정수를 입력하십시오.\n");
        return;
    }

    if (removeCID < 0 || removeCID >= cart_count) {
        printf("잘못된 ID입니다. \n");
        return;
    }

    for (int i = removeCID; i < cart_count - 1; i++) {
        cartlist[i] = cartlist[i + 1];
        cartlist[i].cart_id = i;
    }

    cart_count--;

    printf("상품이 장바구니에서 제거되었습니다.\n");
    SaveCartListToFile(); // 아이템 제거 후 파일에 저장
}



void SelectCartMenu(void) {
    LoadCartListFromFile();
    SaveCartListToFile();

    if (cart_count == 0) {
        printf("장바구니에 담긴 상품이 없습니다.\n");
        return;
    }

    int MenuSelect;

    while (1) {
        ShowCartList();
        if (scanf("%d", &MenuSelect) != 1) {
            flushInputBuffer();
            printf("잘못된 입력입니다. 숫자를 입력하십시오.\n");
            continue;
        }

        switch (MenuSelect) {
        case 1:
            CheckOut();
            break;
        case 2:
            removeFromCart();
            if (cart_count <= 0) { return; } // 장바구니에 상품이 존재하지 않을 경우, customer_Menu로 돌아가기
            break;
        case 3:
            return;
        default:
            printf("잘못된 선택입니다. 다시 시도하십시오.\n");
            break;
        }
    }
}

// 장바구니 보기
void ShowCartList(void) {
    LoadCartListFromFile();
    SaveCartListToFile();

    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("장바구니 상품 수: (%d/80) \n", cart_count);
    printf("%-3s | %-30s | %-10s | %-2s \n", "CID", "상품명", "가격", "ID");
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
    printf("합계: %d\n", sum);
    printf("[1] 체크아웃 하기 [2] 상품 제거하기 [3] 계속 쇼핑하기 \n\n>> ");
    return;
}

int CartSum(void) {
    int sum = 0;
    for (int i = 0; i < cart_count; i++) {
        sum = cartlist[i].cart_item_price + sum;
    }
    return sum;
}


// 체크아웃 및 장바구니의 아이템 제거
void CheckOut(void) {
    int sum = CartSum();
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("구매해 주셔서 감사합니다! 당신의 상품이 곧 배송될 예정입니다. \n");
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("구매 내역 \n");
    printf("%-3s | %-30s | %-10s | %-2s \n", "CID", "상품명", "가격", "ID");
    for (int i = 0; i < cart_count; i++) {
        printf("%-3d | %-30s | %-10d | %-2d \n",
            cartlist[i].cart_id,
            cartlist[i].cart_item_name,
            cartlist[i].cart_item_price,
            cartlist[i].cart_number
        );
    }
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("총합계: %d원 \n", sum);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");

    ResetCartList();

    int MenuSelect;
    while (1) {
        printf("[1] 처음으로 [2] 쇼핑 종료 \n\n>> ");

        if (scanf("%d", &MenuSelect) != 1) {
            flushInputBuffer();
            printf("잘못된 입력입니다. 숫자를 입력하십시오.\n");
            continue;
        }

        switch (MenuSelect) {
        case 1:
            main();
            break;
        case 2:
            printf("쇼핑을 종료합니다.");
            exit();
        default:
            printf("잘못된 선택입니다. 다시 시도하십시오.\n");
            break;
        }
    }
}

// 관리자 전용 설정

// 어드민 로그인
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
        printf("ID 또는 비밀번호가 틀렸습니다.\n");
    }
}

void AdminMenu(void) {
    int admin_menu = 0;
    printf("\n   ###    ########  ##     ## #### ##    ## \n  ## ##   ##     ## ###   ###  ##  ###   ## \n ##   ##  ##     ## #### ####  ##  ####  ## \n##     ## ##     ## ## ### ##  ##  ## ## ## \n######### ##     ## ##     ##  ##  ##  #### \n##     ## ##     ## ##     ##  ##  ##   ### \n##     ## ########  ##     ## #### ##    ## \n");
    while (1) {
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("1. 상품 추가 \n");
        printf("2. 상품 제거 \n");
        printf("3. 로그아웃 \n");
        printf("\n>> ");

        if (scanf("%d", &admin_menu) != 1) {
            flushInputBuffer();
            printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
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
            printf("로그아웃 합니다.\n");
            return;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            break;
        }
    }
}

// 상품 추가(진열)
void addItem(void) {
    if (item_count >= 100) {
        printf("아이템을 더 이상 추가할 수 없습니다.\n");
        return;
    }

    items[item_count].item_number = item_count;

    printf("상품 수 (%d/100) \n", item_count);
    flushInputBuffer();
    printf("아이템 이름 입력 (띄어쓰기 없이) >> ");
    fgets(items[item_count].item_name, sizeof(items[item_count].item_name), stdin);
    removeInputEnter(items[item_count].item_name);

    printf("아이템 설명 입력 (띄어쓰기 가능) >> ");
    fgets(items[item_count].item_desc, sizeof(items[item_count].item_desc), stdin);
    removeInputEnter(items[item_count].item_desc);

    printf("아이템 가격(정수) 입력 >> ");
    if (scanf("%d", &items[item_count].item_price) != 1) {
        flushInputBuffer();
        printf("잘못된 입력입니다. 정수를 입력하세요.\n");
        return;
    }

    printf("상품 추가 - - - - - -\n");
    printf("상품의 ID [%d] | 상품명 : [%s] | 설명 : [%s] | 가격 : [%d] \n",
        items[item_count].item_number,
        items[item_count].item_name,
        items[item_count].item_desc,
        items[item_count].item_price);

    item_count++;
    SaveItemsToFile(); // 아이템 추가 후 파일에 저장
}

// 진열된 상품 제거
void removeItem(void) {
    if (item_count == 0) {
        printf("상품이 존재하지 않습니다.\n");
        return;
    }

    int item_number;
    ShowEveryItem();
    printf("제거할 상품의 ID 입력 >> ");

    if (scanf("%d", &item_number) != 1) {
        flushInputBuffer();
        printf("잘못된 입력입니다. 정수를 입력하십시오.\n");
        return;
    }

    if (item_number < 0 || item_number >= item_count) {
        printf("잘못된 ID입니다. \n");
        return;
    }

    for (int i = item_number; i < item_count - 1; i++) {
        items[i] = items[i + 1];
        items[i].item_number = i;
    }

    item_count--;

    printf("상품 제거 완료.\n");
    SaveItemsToFile(); // 아이템 제거 후 파일에 저장
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

// 그 외 필요하지만 앞에 추가하지 못한 것들

// 상품 목록 전체 보여주기
void ShowEveryItem(void) {
    LoadItemsFromFile();
    SaveItemsToFile();
    printf("상품 수 (%d/100) \n", item_count);
    printf("%-2s | %-30s | %-10s \n", "ID", "상품명", "가격");
    for (int i = 0; i < item_count; i++) {
        printf("%-2d | %-30s | %-10d \n",
            items[i].item_number,
            items[i].item_name,
            items[i].item_price
        );
    }
}

// 최근에 들어온 5개의 아이템(ID가 높은 순으로 5개) 표시
void ShowNewItem(void) {
    LoadItemsFromFile();
    SaveItemsToFile();
    printf("최근에 들어온 상품 \n");
    int recentitem = (item_count <= 5) ? 0 : item_count - 5; // item_count가 5 보다 작거나 같으면 최근에 추가된 아이템 모두 표시
    printf("%-2s | %-30s | %-10s \n", "ID", "상품명", "가격");
    for (int i = recentitem; i < item_count; i++) {
        printf("%-2d | %-30s | %-10d \n",
            items[i].item_number,
            items[i].item_name,
            items[i].item_price
        );
    }
}

// 파일 입출력


// items.txt에서 item의 값 가져오기
void LoadItemsFromFile(void) {
    FILE* file = fopen("items.txt", "r");
    if (file == NULL) {
        printf("items 파일이 존재하지 않습니다. 파일을 생성합니다.\n");
        CreateItemsFile();
        return;
    }

    item_count = 0;
    while (fscanf(file, "%d %s %d %[^\n]s", &items[item_count].item_number, items[item_count].item_name, &items[item_count].item_price, items[item_count].item_desc) == 4) {
        item_count++;
    }

    fclose(file);
}

// items.txt에 item 값 저장하기
void SaveItemsToFile(void) {
    FILE* file = fopen("items.txt", "w");
    if (file == NULL) {
        printf("items 파일이 존재하지 않습니다. 파일을 생성합니다.\n");
        CreateItemsFile();
        return;
    }

    for (int i = 0; i < item_count; i++) {
        fprintf(file, "%d %s %d %s\n", items[i].item_number, items[i].item_name, items[i].item_price, items[i].item_desc);
    }

    fclose(file);
}

// items.txt 생성
void CreateItemsFile(void) {
    FILE* file = fopen("items.txt", "w+");
    fclose(file);
    return;
}

// CartList.txt에서 장바구니 값 가져오기
void LoadCartListFromFile(void) {
    FILE* file = fopen("cartlist.txt", "r");
    if (file == NULL) {
        printf("cartlist 파일이 존재하지 않습니다. 파일을 생성합니다.\n");
        CreateCartListFile();
        return;
    }

    cart_count = 0;
    while (fscanf(file, "%d %s %d %d", &cartlist[cart_count].cart_id, cartlist[cart_count].cart_item_name, &cartlist[cart_count].cart_item_price, &cartlist[cart_count].cart_number) == 4) {
        cart_count++;
    }

    fclose(file);
}

// CartList.txt에 장바구니 값 저장
void SaveCartListToFile(void) {
    FILE* file = fopen("cartlist.txt", "w");
    if (file == NULL) {
        printf("cartlist 파일이 존재하지 않습니다. 파일을 생성합니다.\n");
        CreateCartListFile();
        return;
    }

    for (int i = 0; i < cart_count; i++) {
        fprintf(file, "%d %s %d %d\n", cartlist[i].cart_id, cartlist[i].cart_item_name, cartlist[i].cart_item_price, cartlist[i].cart_number);
    }

    fclose(file);
}

// CartList.txt 생성
void CreateCartListFile(void) {
    FILE* file = fopen("cartlist.txt", "w+");
    fclose(file);
    return;
}

// 장바구니 리셋(CartList.txt 삭제 후 재생성)
void ResetCartList(void) {
    remove(cartlist);
    CreateCartListFile();
}
