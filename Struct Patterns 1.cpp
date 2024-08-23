#include <iostream>
#include <string>
using namespace std;
//Adapter 1
// Класс для работы с PayPal
class PayPalPayment 
{
public:
    void processPayment(double amount) 
    {
        cout << "Processing payment through PayPal: $" << amount << endl;
    }
};

// Класс для работы с Stripe
class StripePayment 
{
public:
    void makePayment(double amount) 
    {
        cout << "Processing payment through Stripe: $" << amount << endl;
    }
};

// Класс для работы с Square
class SquarePayment 
{
public:
    void charge(double amount) 
    {
        cout << "Processing payment through Square: $" << amount << endl;
    }
};

// Новый интерфейс для всех платежных систем
class IPaymentProcessor 
{
public:
    virtual void ProcessPayment(double amount) = 0;
};

// Адаптер для PayPal
class PayPalAdapter : public IPaymentProcessor 
{
private:
    PayPalPayment* paypalPayment;
public:
    PayPalAdapter(PayPalPayment* paypal) 
    {
        paypalPayment = paypal;
    }

    void ProcessPayment(double amount) 
    {
        paypalPayment->processPayment(amount);
    }
};

// Адаптер для Stripe
class StripeAdapter : public IPaymentProcessor 
{
private:
    StripePayment* stripePayment;
public:
    StripeAdapter(StripePayment* stripe) 
    {
        stripePayment = stripe;
    }

    void ProcessPayment(double amount) 
    {
        stripePayment->makePayment(amount);
    }
};

// Адаптер для Square
class SquareAdapter : public IPaymentProcessor 
{
private:
    SquarePayment* squarePayment;
public:
    SquareAdapter(SquarePayment* square) 
    {
        squarePayment = square;
    }

    void ProcessPayment(double amount) 
    {
        squarePayment->charge(amount);
    }
};
//-----------------------------------------------------------
//Adapter 2
// Структура, представляющая стандартный формат данных о клиенте
struct ClientData 
{
    string fullName;
    string address;
    string phoneNumber;
    string email;

    void Display() const 
    {
        cout << "Client Information:\n";
        cout << "Name: " << fullName << "\n";
        cout << "Address: " << address << "\n";
        cout << "Phone: " << phoneNumber << "\n";
        cout << "Email: " << email << "\n";
    }
};

// Внешняя система 1: формат данных о клиенте
struct ExternalClientData1 
{
    string name;
    string residence;
    string contactNumber;
    string mail;
};

// Внешняя система 2: формат данных о клиенте
struct ExternalClientData2 
{
    string firstName;
    string lastName;
    string postalAddress;
    string phone;
    string emailAddress;
};

// Интерфейс адаптера данных
class IClientDataAdapter 
{
public:
    virtual ClientData Convert() = 0;
};

// Адаптер для внешней системы 1
class ExternalClientData1Adapter : public IClientDataAdapter 
{
    ExternalClientData1 extData;

public:
    ExternalClientData1Adapter(const ExternalClientData1& extData) : extData(extData) {}

    ClientData Convert() override 
    {
        ClientData clientData;
        clientData.fullName = extData.name;
        clientData.address = extData.residence;
        clientData.phoneNumber = extData.contactNumber;
        clientData.email = extData.mail;
        return clientData;
    }
};

// Адаптер для внешней системы 2
class ExternalClientData2Adapter : public IClientDataAdapter 
{
    ExternalClientData2 extData;

public:
    ExternalClientData2Adapter(const ExternalClientData2& extData) : extData(extData) {}

    ClientData Convert() override 
    {
        ClientData clientData;
        clientData.fullName = extData.firstName + " " + extData.lastName;
        clientData.address = extData.postalAddress;
        clientData.phoneNumber = extData.phone;
        clientData.email = extData.emailAddress;
        return clientData;
    }
};
//-----------------------------------------------------------
//Bridge
// Интерфейс реализации хранения документов
class IStorage 
{
public:
    virtual void Store(string content) = 0;
};

// Реализация хранения на локальном диске
class LocalStorage : public IStorage 
{
public:
    void Store(string content) override 
    {
        cout << "Saving to Local Storage: " << content << endl;
    }
};

// Реализация хранения в облаке
class CloudStorage : public IStorage 
{
public:
    void Store(string content) override 
    {
        cout << "Saving to Cloud Storage: " << content << endl;
    }
};

// Реализация хранения в базе данных
class DatabaseStorage : public IStorage 
{
public:
    void Store(string content) override 
    {
        cout << "Saving to Database Storage: " << content << endl;
    }
};

// Абстракция документа
class Document 
{
protected:
    IStorage* storage;

public:
    Document(IStorage* s) : storage(s) {}
    virtual void Save() = 0;
};

// Абстракция текстового документа
class TextDocument : public Document 
{
public:
    TextDocument(IStorage* s) : Document(s) {}
    void Save() override 
    {
        storage->Store("Document content here...");
    }
};

// Абстракция PDF-документа
class PDFDocument : public Document 
{
public:
    PDFDocument(IStorage* s) : Document(s) {}
    void Save() override 
    {
        storage->Store("Document content here...");
    }
};

// Абстракция XML-документа
class XMLDocument : public Document 
{
public:
    XMLDocument(IStorage* s) : Document(s) {}
    void Save() override 
    {
        storage->Store("Document content here...");
    }
};
//-----------------------------------------------------------
//Decorator
// Базовый интерфейс для заказа
class IOrder 
{
public:
    virtual double GetTotalCost() = 0;
    virtual string GetDescription() = 0;
};

class BasicOrder : public IOrder 
{
public:
    double GetTotalCost() override 
    {
        return 50.0;
    }

    string GetDescription() override 
    {
        return "Basic Order";
    }
};

// Базовый класс для декораторов
class OrderDecorator : public IOrder 
{
protected:
    IOrder* wrappedOrder;
public:
    OrderDecorator(IOrder* order) : wrappedOrder(order) {}

    double GetTotalCost() override 
    {
        return wrappedOrder->GetTotalCost();
    }

    string GetDescription() override 
    {
        return wrappedOrder->GetDescription();
    }
};

// Декоратор для добавления упаковки
class GiftWrapDecorator : public OrderDecorator 
{
public:
    GiftWrapDecorator(IOrder* order) : OrderDecorator(order) {}

    double GetTotalCost() override 
    {
        return wrappedOrder->GetTotalCost() + 5.0;
    }

    string GetDescription() override 
    {
        return wrappedOrder->GetDescription() + " with Gift Wrap";
    }
};

// Декоратор для добавления ускоренной доставки
class ExpressDeliveryDecorator : public OrderDecorator 
{
public:
    ExpressDeliveryDecorator(IOrder* order) : OrderDecorator(order) {}

    double GetTotalCost() override 
    {
        return wrappedOrder->GetTotalCost() + 20.0;
    }

    string GetDescription() override 
    {
        return wrappedOrder->GetDescription() + " with Express Delivery";
    }
};

// Декоратор для добавления гарантии
class WarrantyDecorator : public OrderDecorator 
{
public:
    WarrantyDecorator(IOrder* order) : OrderDecorator(order) {}

    double GetTotalCost() override 
    {
        return wrappedOrder->GetTotalCost() + 25.0;
    }

    string GetDescription() override 
    {
        return wrappedOrder->GetDescription() + " with Warranty";
    }
};

// Декоратор для добавления страхования
class InsuranceDecorator : public OrderDecorator 
{
public:
    InsuranceDecorator(IOrder* order) : OrderDecorator(order) {}

    double GetTotalCost() override 
    {
        return wrappedOrder->GetTotalCost() + 30.0;
    }

    string GetDescription() override 
    {
        return wrappedOrder->GetDescription() + " with Insurance";
    }
};


int main() 
{
    cout << "Adapter 1" << endl;
    PayPalPayment* paypal = new PayPalPayment();
    StripePayment* stripe = new StripePayment();
    SquarePayment* square = new SquarePayment();

    // Используем все платежные системы через адаптеры
    IPaymentProcessor* paypalProcessor = new PayPalAdapter(paypal);
    IPaymentProcessor* stripeProcessor = new StripeAdapter(stripe);
    IPaymentProcessor* squareProcessor = new SquareAdapter(square);

    paypalProcessor->ProcessPayment(150.75);    // Processing payment through PayPal: $150.75
    stripeProcessor->ProcessPayment(200.00);    // Processing payment through Stripe: $200.00
    squareProcessor->ProcessPayment(300.50);    // Processing payment through Square: $300.50   

    delete paypalProcessor;
    delete stripeProcessor;
    delete squareProcessor;

    delete paypal;
    delete stripe;
    delete square;

    cout << "------------------------------------------------------\n";
    cout << "Adapter 2" << endl;

    // Данные от внешней системы 1
    ExternalClientData1 extData1 = { "John Doe", "123 Main St", "555-1234", "john@example.com" };

    // Данные от внешней системы 2
    ExternalClientData2 extData2 = { "Jane", "Smith", "456 Oak Ave", "555-5678", "jane.smith@example.com" };

    // Используем адаптеры для конвертации данных
    IClientDataAdapter* adapter1 = new ExternalClientData1Adapter(extData1);
    ClientData client1 = adapter1->Convert();
    client1.Display();

    IClientDataAdapter* adapter2 = new ExternalClientData2Adapter(extData2);
    ClientData client2 = adapter2->Convert();
    client2.Display();

    delete adapter1;
    delete adapter2;

    cout << "------------------------------------------------------\n";
    cout << "Brigde" << endl;
    // Создаем текстовый документ, хранимый на локальном диске
    Document* textDoc = new TextDocument(new LocalStorage());   // Saving Text Document to Local Storage: Document content here...
    textDoc->Save();

    // Создаем PDF документ, хранимый в облаке
    Document* pdfDoc = new PDFDocument(new CloudStorage());     // Saving PDF Document to Cloud Storage: Document content here...
    pdfDoc->Save();

    // Создаем XML документ, хранимый в базе данных
    Document* xmlDoc = new XMLDocument(new DatabaseStorage());  // Saving XML Document to Database Storage: Document content here...
    xmlDoc->Save();

    delete textDoc;
    delete pdfDoc;
    delete xmlDoc;

    cout << "------------------------------------------------------\n";
    cout << "Decorator" << endl;
    // Создаем базовый заказ
    IOrder* order = new BasicOrder();
    cout << order->GetDescription() << ": $" << order->GetTotalCost() << endl;

    // Добавляем упаковку подарков
    order = new GiftWrapDecorator(order);
    cout << order->GetDescription() << ": $" << order->GetTotalCost() << endl;

    // Добавляем ускоренную доставку
    order = new ExpressDeliveryDecorator(order);
    cout << order->GetDescription() << ": $" << order->GetTotalCost() << endl;

    // Добавляем гарантию
    order = new WarrantyDecorator(order);
    cout << order->GetDescription() << ": $" << order->GetTotalCost() << endl;

    // Добавляем страхование
    order = new InsuranceDecorator(order);
    cout << order->GetDescription() << ": $" << order->GetTotalCost() << endl;

    // Ожидаемый вывод:
    // Basic Order: $50
    // Basic Order with Gift Wrap: $55
    // Basic Order with Gift Wrap and Express Delivery: $75
    // Basic Order with Gift Wrap, Express Delivery, and Warranty: $100
    // Basic Order with Gift Wrap, Express Delivery, Warranty, and Insurance: $130

    delete order;




    return 0;

}