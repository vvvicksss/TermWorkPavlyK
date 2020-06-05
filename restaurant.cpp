#include <iostream>
#include <string>

using namespace std;


// клас для формування страви
class dish 
{
    public:
        string name; // назва страви
        float cost; // ціна за 100 грам
        // інгредієнти обмежені кількістю 20 
        string ingredients[20]; // назви інгредієнтів
        int weight[20]; // вага інгредієнтів

        string get_name()
        {
            return  name;
        }
};


// клас для відкриття ресторану
class business 
{
    public:
        int money;
        int get_money()
        {
            return 0;
        }
};


// клас-наслідник бізнесу - ресторан
class restaurant : public business 
{
    public:
        string name;  // назва ресторану
        float money = 0; // кількість зароблених грошей
        // кількість страв в ресторані обмежена числом 100
        dish dishes[100]; // масив для збереження інформації про страву
        int dishes_a = 0; // кількість страв в ресторані

        restaurant(string n) 
        {
            name = n;
        }
    
    // функція для створення страви
    void create()
    {
        /*
         формування страви
         */
        dishes[dishes_a] = dish();  // масив страв розмірністю кількості страв
        string name;  // назва страви
        int n;  // кількість інгредієнтів
        float p;  // ціна страви за 100 грам
        cout << "введіть назву страви: ";
        cin >> name;
        dishes[dishes_a].name = name;
        cout << "введіть ціну страви за 100 грам: ";
        cin >> p;
        dishes[dishes_a].cost = p;
        cout << "введіть кількість інгредієнтів: ";
        cin >> n;
        string in_name;  // назва інгредієнта
        int w;  // вага інгредієнта
        for (int i = 0; i < n; i++)
        {
            cout << "введіть назву інгредієнта " << i + 1 << ": ";
            cin >> in_name;
            cout << "введіть вагу інгредієнта " << i + 1 << ": ";
            cin >> w;
            dishes[dishes_a].ingredients[i] = in_name;
            dishes[dishes_a].weight[i] = w;
        }
        dishes_a++;
    }
    
    // доступ до назви
    string get_name() 
    {
        return name;
    }
    
    // встановлення назви
    void set_name(string n) 
    {
        name = n;
    }
    
    // доступ до капіталу
    int get_money(int m) 
    {
        return money;
    }
    
    // встановлення капіталу
    void set_money(int m) 
    {
        if (m < 0) 
        {
            throw "грошей не може бути менше 0 при відкритті бізнесу";
        }
        money = m;
    }

    // функція для пошуку страви при формуванні замовлення
    int find_dish(string name)
    {
        // пошук страви за іменем 
        for (int i = 0; i < dishes_a; i++)
        {
            if (dishes[i].name == name)
            {
                return i;
            }
        }
        return -1; // якщо страва не існує повертаємо -1
    }
    
    // функція для створення замовлення
    string order()
    {
        /*
        функція для формування замовлення
        повертає результат замовлення та суму замоалення до сплати 
        */
        int n;
        cout << "введіть кількість страв, які ви хочете замовити: ";
        cin >> n;

        string ans = "";
        float price = 0;

        string d_name;  // назва страви
        float w;  // вага страви
        for (int i = 0; i < n; i++)
        {
            cout << "введіть назву страви, яку ви хочете замовити: ";
            cin >> d_name;
            cout << "введіть вагу страви, яку ви хочете замовити: ";
            cin >> w;
            int indx = find_dish(d_name);  // пошук страви за іменем
            // перевірка на наявність даної страви
            if (indx == -1)
            { 
                ans += "страви  " + d_name + " в ресторані нема\n";
            } 
            else 
            {
                // вичисляємо вартість страви
                float dish_price = dishes[indx].cost * (w/100);
                ans += "страва " + d_name + " коштує " + to_string(dish_price) + "грн\n";
                price += dish_price;
            }
        }
        ans += "замовлення коштує " + to_string(price) + "грн\n";
        return ans;
    }
};


// генерація стартового капіталу
int generate_start_cap() 
{
    return rand() % 10000 - 500;
}


int main() 
{
    srand(0);
    restaurant r = restaurant("Flower"); //  створення ресторану

    int state = 0;

    int (*fcnPtr)() = generate_start_cap;  // стартовий капітал

    r.set_money(fcnPtr());  // встановлення капіталу

    while (true)
    {
        cout << endl << "додати страву: 1" << endl
             << "оформити замовлення: 2" << endl
             << "дізнатись прибуток ресторану: 3" << endl
             << "зачинити ресторан: 4 " << endl;

        cin >> state;
        if (state == 1) 
        {
            r.create();  // формуємо страву
        }

        if (state == 2) 
        {
            cout << r.order() << endl;  // формуємо замовлення
        }

        if (state == 3) 
        {
            cout << "на рахунку ресторану " << r.business::get_money() << "грн" << endl;
        }

        if (state == 4) 
        {
            break;  // виходимо з програми
        }

    }

    return 0;
}
