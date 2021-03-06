#include "CommandHandlers.h"
#include "../DataManager/DataManager.h"
#include "Globals.h"
#include "../Products/Products.h"

/*Command executors listed alphabetically*/

Result addNewProduct()
{
	Product* prod;
	string command;
	cout << Message("[help] - shows all the possible product types, that can be created", LOG_MSG)
		 << Message("[continue] - goes to creating a new product", LOG_MSG);
	getline(cin, command);
	while (command == "help")
	{
		cout << Message("Products:", LOG_MSG);
		cout << Message("Appliance", LOG_MSG); 
		cout << Message("Audio&TV", LOG_MSG); 
		cout << Message("Laptop&computer", LOG_MSG); 
		cout << Message("Phone&tablet", LOG_MSG); 
		cout << Message("Photo&videocamera", LOG_MSG); 
		cout << Message("Drink", LOG_MSG); 
		cout << Message("Food", LOG_MSG); 
		cout << Message("Accessory", LOG_MSG); 
		cout << Message("Clothing", LOG_MSG); 
		cout << Message("Footwear", LOG_MSG); 
		cout << Message("Cosmetic", LOG_MSG); 
		cout << Message("Detergent", LOG_MSG); 
		cout << Message("Personal hygiene", LOG_MSG);
		getline(cin, command);
	}
	if (command == "continue")
	{
		string type;
		int quantity;
		cout << Message("Type", CONTEXT_MSG);
		getline(cin, type);
		if (type == "Appliance" || type == "appliance")
		{
			prod = new Appliance();
			prod->input();
			DataManager manager;
			manager.saveProduct(*prod);
			cout << Message("Quantity", CONTEXT_MSG);
			cin >> quantity;
			manager.setQuantity(prod->getId(), quantity);
		}
		else if (type == "Audio&TV" || type == "audio&TV")
		{
			prod = new AudioAndTv();
			prod->input();
			DataManager manager;
			manager.saveProduct(*prod);
			cout << Message("Quantity", CONTEXT_MSG);
			cin >> quantity;
			manager.setQuantity(prod->getId(), quantity);
		}
		else if (type == "Laptop&computer" || type == "laptop&computer")
		{
			prod = new LaptopAndComputer();
			prod->input();
			DataManager manager;
			manager.saveProduct(*prod);
			cout << Message("Quantity", CONTEXT_MSG);
			cin >> quantity;
			manager.setQuantity(prod->getId(), quantity);
		}
		else if (type == "Phone&tablet" || type == "phone&tablet")
		{
			prod = new PhoneAndTablet();
			prod->input();
			DataManager manager;
			manager.saveProduct(*prod);
			cout << Message("Quantity", CONTEXT_MSG);
			cin >> quantity;
			manager.setQuantity(prod->getId(), quantity);
		}
		else if (type == "Photo&videocamera" || type == "photo&videocamera")
		{
			prod = new PhotoAndVideoCamera();
			prod->input();
			DataManager manager;
			manager.saveProduct(*prod);
			cout << Message("Quantity", CONTEXT_MSG);
			cin >> quantity;
			manager.setQuantity(prod->getId(), quantity);
		}
		else if (type == "Drink" || type == "drink")
		{
			prod = new Drink();
			prod->input();
			DataManager manager;
			manager.saveProduct(*prod);
			cout << Message("Quantity", CONTEXT_MSG);
			cin >> quantity;
			manager.setQuantity(prod->getId(), quantity);
		}
		else if (type == "Food" || type == "food")
		{
			prod = new Food();
			prod->input();
			DataManager manager;
			manager.saveProduct(*prod);
			cout << Message("Quantity", CONTEXT_MSG);
			cin >> quantity;
			manager.setQuantity(prod->getId(), quantity);
		}
		else if (type == "Accessory" || type == "accessory")
		{
			prod = new Accessory();
			prod->input();
			DataManager manager;
			manager.saveProduct(*prod);
			cout << Message("Quantity", CONTEXT_MSG);
			cin >> quantity;
			manager.setQuantity(prod->getId(), quantity);
		}
		else if (type == "Clothing" || type == "clothing")
		{
			prod = new Clothing();
			prod->input();
			DataManager manager;
			manager.saveProduct(*prod);
			cout << Message("Quantity", CONTEXT_MSG);
			cin >> quantity;
			manager.setQuantity(prod->getId(), quantity);
		}
		else if (type == "Footwear" || type == "footwear")
		{
			prod = new Footwear();
			prod->input();
			DataManager manager;
			manager.saveProduct(*prod);
			cout << Message("Quantity", CONTEXT_MSG);
			cin >> quantity;
			manager.setQuantity(prod->getId(), quantity);
		}
		else if (type == "Cosmetic" || type == "cosmetic")
		{
			prod = new Cosmetic();
			prod->input();
			DataManager manager;
			manager.saveProduct(*prod);
			cout << Message("Quantity", CONTEXT_MSG);
			cin >> quantity;
			manager.setQuantity(prod->getId(), quantity);
		}
		else if (type == "Detergent" || type == "detergent")
		{
			prod = new Detergent();
			prod->input();
			DataManager manager;
			manager.saveProduct(*prod);
			cout << Message("Quantity", CONTEXT_MSG);
			cin >> quantity;
			manager.setQuantity(prod->getId(), quantity);
		}
		else if (type == "Personal hygiene" || type == "personal hygiene")
		{
			prod = new PersonalHygiene();
			prod->input();
			DataManager manager;
			manager.saveProduct(*prod);
			cout << Message("Quantity", CONTEXT_MSG);
			cin >> quantity;
			manager.setQuantity(prod->getId(), quantity);
		}
		else
		{
			return Result("Unknown type.", NOT_SUCCESSFUL);
		}
		cin.get();
	}
	else
	{
		return Result("Unknown command.", NOT_SUCCESSFUL);
	}

	delete[] prod;
	cout << Message("New product is added to the assortment.", LOG_MSG);
	return Result();
}

Result buyAllProductFromCart()
{
	if (cart.size() == 1)
	{
		return Result("Your cart is empty.", SUCCESSFUL);
	} else
	{
		if (cart.size() == 0)
		{
			cout << Message("Your cart is empty", LOG_MSG);
			return Result();
		}
		List<Product*>::iterator end = cart.end();
		for (List<Product*>::iterator it = cart.begin(); it != end; it++)
		{
			DataManager().changeQuantity((*it)->getId(), -1);
			ofstream stream(to_string(currentUser.getId()) + ".txt", ios_base::app);
			if (!stream.is_open())
			{
				return Result("Couldn't open file for writing...", TOTAL_ERROR);
			}
			stream << *it << '\n';
			stream.close();
			
			(*it)->output();
		}
	}
	return Result("You bought all products.", SUCCESSFUL);
}

Result buyOneElementById()
{
	cout << Message("Enter product id", CONTEXT_MSG);
	int id;
	cin >> id;
	cin.get();
	
	Product* product = DataManager().getProductById(id);
	if (product == nullptr)
	{
		return Result("There is no product with such an id", NOT_SUCCESSFUL);
	}
	DataManager().changeQuantity(product->getId(), -1);
	ofstream stream(to_string(currentUser.getId()) + ".txt", ios_base::app);
	if (!stream.is_open())
	{
		return Result("Couldn't open file for writing...", TOTAL_ERROR);
	}
	stream << *product << '\n';
	stream.close();

	cout << Message("You bought: ", LOG_MSG);
	product->output();
	return Result();
}

Result addProductToCart()
{
	cout << Message("Enter id of product you want to add to cart : ", LOG_MSG);
	int id;
	cin >> id;
	DataManager manager;
	Product* product = manager.getProductById(id);
	cart.pushBack(product);
	cout << Message("You have added to cart : ", LOG_MSG) ;
	cout << *product;
	return Result();
}

Result changeAmount()
{
	int id;
	cout << Message("Id", CONTEXT_MSG);
	cin >> id;

	int quantity;
	DataManager manager;

	string message = string("Current quantity of product with id ") + to_string(id) +
		string(": ") + to_string(manager.getQuantity(id));
	cout << Message(message, LOG_MSG);

	cout << Message("Enter new quantity", CONTEXT_MSG);
	cin >> quantity;
	cin.get();
	manager.setQuantity(id, quantity);

	cout << Message("New quantity is added to the assortment.", LOG_MSG);
	return Result();
}

Result changeProduct()
{
	int id = 0;
	cout << Message("Enter id", CONTEXT_MSG);
	cin >> id;
	cin.get();

	DataManager manager;
	Product *prod = manager.getProductById(id);
	if (prod == nullptr)
	{
		return Result("Invalid id.", NOT_SUCCESSFUL);
	}

	prod->input();

	string message = string("Current quantity of product with id ") + to_string(id) +
		string(": ") + to_string(manager.getQuantity(id));
	cout << Message(message, LOG_MSG);
	cout << Message("Enter new quantity", CONTEXT_MSG);
	int quantity = 0;
	cin >> quantity;
	cin.get();

	manager.removeProductById(id);
	manager.saveProduct(*prod);
	manager.setQuantity(id, quantity);

	delete[] prod;
	return Result("Product is changed.", SUCCESSFUL);
}

Result createAdmin()
{
	int id;
	cout << Message("Enter id of the account", CONTEXT_MSG);
	cin >> id;
	cin.get();

	DataManager manager;
	User *user = nullptr;

	try
	{
		user = manager.getUserById(id);
	} catch (exception exp)
	{
		return Result(exp.what(), NOT_SUCCESSFUL);
	}

	if (user == nullptr)
	{
		return Result("The id is invalid. Please try again.", NOT_SUCCESSFUL);
	}

	if (user->getRole() == Access::ADMIN)
	{
		cout << Message("The account already has administrator rights.", LOG_MSG);
		return Result();
	}

	user->setRole(Access::ADMIN);
	manager.removeUserById(id);
	manager.saveUser(*user);

	cout << Message("The account was granted administrator rights.", LOG_MSG);
	return Result();
}

Result createUser()
{
	using std::cin;
	User newUser;
	newUser.input();
	DataManager manager;
	manager.saveUser(newUser);
	cin.get();

	cout << Message("The account was created successfully", LOG_MSG);
	return Result();
}

Result exit()
{
	return Result(EXIT);
}

Result help()
{
	for (int i = 0; i < numOfCommands; i++)
	{
		if (currentUser.getRole() & commands[i].getAccessLevel())
			cout << Message("[" + commands[i].getName() + "] - " + commands[i].getDescription(), LOG_MSG);
	}
	return Result();
}

Result logIn()
{
	using std::cin;

	cout << Message("Name", CONTEXT_MSG);
	string name;
	getline(cin, name, '\n');
	cout << Message("Password", CONTEXT_MSG);
	string password;
	getline(cin, password, '\n');

	/* Checking the database */
	
	DataManager dataManager;
	User* existingUser = dataManager.getUserByLogin(name, password);
	
	if (existingUser == nullptr) //User with this login exists
	{
		return Result("Authentication failed\nPlease, check your name, password and try again", NOT_SUCCESSFUL);
	}
	else
	{
		currentUser = *existingUser;
		cout << Message("Authentication successful\nWelcome, " + name + "!", LOG_MSG);
	}

	delete existingUser;
	return Result();
}

Result logOut()
{
	currentUser = User();

	cout << Message("You logged out successfully.", LOG_MSG);
	return Result();
}

Result removeProductFromAssortment()
{
	int id;
	cout << Message("Enter id of product you want to remove:", CONTEXT_MSG);
	cin >> id;
	cin.get();
	DataManager manager;
	manager.removeProductById(id);

	cout << Message("The product is removed from the assortment.", LOG_MSG);
	return Result();
}

Result removeProductFromCart()
{
	int ID;
	bool option;

	if(cart.size() == 0)
	{
		cout << Message("Your cart is empty.", LOG_MSG);
		return Result();
	}
	else if(cart.size() == 1)
	{
		option = true;
		cout << Message("You currently have one product in your cart.", CONTEXT_MSG);
	}
	else
	{
		option = false;
		cout << Message("You currently have " + to_string(cart.size()) + " products in your cart.", CONTEXT_MSG)
			 << Message("Which product would you like to remove from your cart?", CONTEXT_MSG)
			 << Message("Input ID:", CONTEXT_MSG);
		cin >> ID;
	}

	cout << Message("Are you sure you want to remove this product? (y/n)", CONTEXT_MSG);
	char answer;
	cin >> answer;
	int stupidityCount = 0;
	while(answer != 'y' && answer != 'n')
	{
		stupidityCount++;
		if(stupidityCount >= 3)
		{
			cout << Message("You aren't smart, are you?..", ALERT_MSG);
		}
		else
		{
			cout << Message("You may have misunderstood me.", LOG_MSG);
		}
		cout << Message("Are you sure you want to remove this product? (y/n)", CONTEXT_MSG);
		cin >> answer;
	}
	try
	{
		switch(answer)
		{
		case 'y': 
			DataManager manager;
			cart.erase(option ? cart.begin() : cart.find(manager.getProductById(ID), cart.begin(), cart.end()));
			return Result("Operation successful.", SUCCESSFUL);
			break;
		case 'n': 
			return Result("Operation cancelled.", SUCCESSFUL);
			break;
		}
	}
	catch(exception exc)
	{
		return Result(exc.what(), NOT_SUCCESSFUL);
	}

	return Result();
}

Result removeUser()
{
	int id = 0;
	cout << Message("Enter id of the account", CONTEXT_MSG);
	cin >> id;

	if (id == currentUser.getId())
	{
		return Result("You cannot delete yourself.", SUCCESSFUL);
	}

	DataManager manager;

	try
	{
		manager.removeUserById(id);
	} catch (exception exp)
	{
		cin.get();
		return Result(exp.what(), NOT_SUCCESSFUL);
	}

	return Result("The user was deleted successfully.", SUCCESSFUL);
}

Result showCart()
{
	if(cart.begin() == cart.end())
	{
		cout << Message("Your cart is empty.", CONTEXT_MSG);
		return Result(SUCCESSFUL);
	}

	List<Product*>::iterator end = cart.end();
	for (List<Product*>::iterator iterator = cart.begin(); iterator != end; iterator++)
	{
		cout << *iterator;
	}
	return Result();
}

Result showProducts()
{
	List<Product*> allProducts = DataManager().readAllProducts();
	if (allProducts.size() == 0)
	{
		cout << Message("There are no products in our shop, we are so poor.", LOG_MSG);
		return Result();
	}

	auto end = allProducts.end();

	for (auto it = allProducts.begin(); it != end; it++)
	{
		cout << Message(string(typeid(**it).name()).substr(6), LOG_MSG);
		(*it)->output();
		cout << endl;
	}

	for (auto it = allProducts.begin(); it != end; it++)
	{
		delete *it;
	}
	
	cout << Message("Listing completed.", LOG_MSG);
	return Result();
}

Result showPurchaseHistory()
{
	ifstream stream;
	stream.open(to_string(currentUser.getId()) + ".txt", std::ifstream::in);
	if (!stream.is_open())
	{
		return Result("Couldn't open file for writing...", TOTAL_ERROR);
	}

	while (!stream.eof())
	{
		string prod;
		stream >> prod;
		cout << Message(prod, LOG_MSG);
	}
	stream.close();

	return Result();
}

Result showStats()
{
	DataManager manager;
	map<Product*, int> map = manager.readStatistics();
	for (auto it = map.begin(); it != map.end(); ++it)
	{
		it->first->output();
		cout << Message("Quantity: " + to_string(it->second), LOG_MSG);
		cout << endl;
	}

	cout << Message("Listing completed.", LOG_MSG);
	return Result();
}

Result showUsers()
{
	DataManager manager;
	List<User*> list = manager.readAllUsers();
	auto iter = list.begin();

	while(iter != list.end())
	{
		int temp = 0;
		(*iter)->print();
		temp ++;
		iter ++;

		if((temp % 5) == 0)
		{
			cout << Message("Press Enter to continue.", LOG_MSG);
			cin.get();
		}

		cout << endl;
	}

	cout << Message("Listing completed.", LOG_MSG);
	return Result();
}
