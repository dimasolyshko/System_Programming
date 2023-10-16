#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ONE = 1;
const int TWO = 2;
const int THREE = 3;
const int FOUR = 4;
const int FIVE = 5;
const int SIX = 6;
const int SEVEN = 7;
const int EIGHT = 8;



class Window {
public:
    int id;
    int height;
    int width;
    int memoryNeeded;
    bool areAdministratorRightsGranted;
    bool isShown;

    Window(int id, int height, int width, bool areAdministratorRightsGranted) {
        this->id = id;
        this->height = height;
        this->width = width;
        this->areAdministratorRightsGranted = areAdministratorRightsGranted;
        this->memoryNeeded = 0;
        this->isShown = false;
    }

    void doWork(int workAmount) {
        memoryNeeded += workAmount;
    }

    void showOrHide() {
        isShown = !isShown;
    }
};

class Tab {
public:
    string url;

    Tab(string url) {
        this->url = url;
    }
};

class BrowserWindow : public Window {
public:
    vector<Tab> tabs;
    string username;
    int currentTabIndex = -1;

    BrowserWindow(int id, int height, int width, bool areAdministratorRightsGranted, string username, int currentTab) : Window(id, height, width, areAdministratorRightsGranted)
    {
        this->username = username;
        this->currentTabIndex = currentTab;
    }

    BrowserWindow(int id, int height, int width, bool areAdministratorRightsGranted, string username) : Window(id, height, width, areAdministratorRightsGranted)
    {
        this->username = username;
    }

    void updateMemoryNeeded() {
        memoryNeeded = 0;
        doWork(tabs.size());
        if (currentTabIndex >= 0 && currentTabIndex < tabs.size()) {
            doWork(tabs[currentTabIndex].url.length());
        }
    }

    void addTab(string url) {
        tabs.emplace_back(url);
        updateMemoryNeeded();
    }

    bool switchTab(int tabIndex) {
        if (tabIndex >= 0 && tabIndex < tabs.size()) {
            if (currentTabIndex != tabIndex) {
                currentTabIndex = tabIndex;
                updateMemoryNeeded();
                cout << "Теперь основная вкладка " << tabs[tabIndex].url << endl;
                return true;
            }
            else {
                cout << "Вы и так на этой вкладке" << endl;
            }
        }
        else {
            cout << "Неправильный индекс" << endl;
        }
        return false;
    }

    bool closeTab(int tabIndex) {
        if (tabIndex >= 0 && tabIndex < tabs.size()) {
            tabs.erase(tabs.begin() + tabIndex);
            cout << "закрытая вкладка : " << tabIndex << endl;
            if (currentTabIndex >= tabIndex)
            {
                currentTabIndex--;
            }
            updateMemoryNeeded();
            return true;
        }
        else {
            cout << "неправильный индекс" << endl;
        }
        return false;
    }

    void searchHistory(string query) {
        cout << "Поиск результата по " << query << "':" << endl;
        for (int i = 0; i < tabs.size(); ++i) {
            if (tabs[i].url.find(query) != string::npos) {
                cout << "Вкладка " << i + 1 << ": " << tabs[i].url << endl;
            }
        }
    }

    void changeUser(string newUsername) {
        username = newUsername;
    }

    void show()
    {
        cout << "Все вкладки пользователя " << this->username << endl;
        for (int i = 0; i < tabs.size(); i++)
        {
            cout << i + 1 << " " << tabs[i].url << endl;
        }
        
        if (currentTabIndex != -1)
        {
            cout << "Основная вкладка: " << currentTabIndex + 1 << " " << tabs[currentTabIndex].url << endl;
        }
    }
};

int main() {

    BrowserWindow browser(1, 1024, 768, true, "user1");
    string NameOfTab, NameOfUser;
    int tabIndex = 0;

    setlocale(LC_ALL, "rus");

    while (true)
    {
        int CaseIndex = 0;
        cout << "1.Добавить вкладку" << endl
            << "2.Поменять основную вкладку" << endl
            << "3.Удалить вкладку" << endl
            << "4.Найти вкладку по истории вкладок" << endl
            << "5.Поменять User" << endl
            << "6.показать затраченную память" << endl
            << "7.Показать все вкладки" << endl
            << "8.Выход" << endl
            << "Ваш выбор: " << endl;
        cin >> CaseIndex;
        switch(CaseIndex)
        {
            case ONE:
            {
                cout << "Введите URL вкладки, которую хотите добавить ";
                cin >> NameOfTab;
                browser.addTab(NameOfTab);
                break; 
            }
                
            case TWO:
            {
                cout << "Введите индекс вкладки, которую хотите сделать основной: ";
                cin >> tabIndex;
                browser.switchTab(--tabIndex);
                break;
            }
                
            case THREE:
            {
                cout << "Введите индекс вкладки, которую хотите удалить ";
                cin >> tabIndex;
                browser.closeTab(--tabIndex);
                break;
            }

            case FOUR:
            {
                cout << "Введите URL или ключевое имя вкладки, которую хотите найти ";
                cin >> NameOfTab;
                browser.searchHistory(NameOfTab);
                break;
            }

            case FIVE:
            {
                cout << "Введите новое имя пользователя ";
                cin >> NameOfUser;
                browser.changeUser(NameOfUser);
                break;
            }
            case SIX:
            {
                cout << "Затраченная память " << browser.memoryNeeded << endl;
                break;
            }
            case SEVEN:
            {
                browser.show();
                break;
            }
            case EIGHT:
                return 0;
            default:
                cout << "Неправильный символ" << endl;
                break;
        }
    }
}
