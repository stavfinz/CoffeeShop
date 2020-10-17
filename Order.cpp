#pragma warning(disable : 4996)

#include "Order.h"
#include "Product.h"
#include "Employee.h"
#include "Customer.h"
#include "utils.h"


Order::Order(const Employee& employee, const Customer& customer) : employee(employee), customer(customer)
{
	this->numItems = 0;
	this->itemsMaxSize = 20;
	this->items = new Product * [itemsMaxSize];
}

Order::Order(const Order& other) : employee(other.employee), customer(other.customer)
{
	*this = other;
}

Order::~Order()
{
	for (int i = 0; i < numItems; i++)
	{
		delete items[i];
	}
	delete[] items;
	//deleteArray((void**)items, itemsMaxSize, numItems);
}

const Order& Order::operator=(const Order& other)
{
	if (this != &other)
	{
		//deleteArray((void**)items, numItems, sizeof(Product*));
		
		for (int i = 0; i < numItems; i++)
		{
			delete items[i];
		}
		delete[] items;
		
		/*employee = other.employee;				//	todo: check this
		customer = other.customer;*/
		numItems = 0;
		itemsMaxSize = other.itemsMaxSize;
		items = new Product * [itemsMaxSize];
		for (int i = 0; i < numItems; i++)
		{
			addItem(other[i]);
		}
	}
	return *this;
}

const Order& Order::operator=(Order&& other)
{
	if (this != &other)
	{
		numItems = other.numItems;
		itemsMaxSize = other.itemsMaxSize;
		std::swap(items, other.items);
	}
	return *this;
}

Order Order::operator+(const Order& order)
{
	Order combined(*this);
	for (int i = 0; i < order.numItems; i++)
	{
		combined.addItem(order[i]);
	}
	return combined;
}

bool Order::addItem(const Product& product)
{
	if (numItems == itemsMaxSize)
	{
		itemsMaxSize *= 2;
		Product** tempArr = new Product * [itemsMaxSize];
		memcpy(tempArr, items, numItems * sizeof(Product*));
		std::swap(tempArr, items);
		delete[] tempArr;
		//increaseArraySize((void**)items, numItems, itemsMaxSize, sizeof(Product*));
	}
	items[numItems++] = product.clone();
	return true;
}

int Order::getTotalCalories() const
{
	int totalCalories = 0;
	for (int i = 0; i < numItems; i++)
	{
		totalCalories += items[i]->getCalories();
	}
	return totalCalories;
}

double Order::getOrderProfit() const
{
	double sumProfit = 0;
	for (int i = 0; i < numItems; i++)
	{
		sumProfit += (items[i]->getPrice() - items[i]->getCost());
	}
	return sumProfit;
}

ostream& operator<<(ostream& os, const Order& order)
{
	os << "Order, Employee: " << order.getEmployee() << " Profit: " << order.getOrderProfit() << endl;
	return os;
}