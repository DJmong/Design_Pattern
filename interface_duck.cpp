#include <iostream>
#include <string>
#include <sstream>


class flyBehavior{
public:
	virtual void fly() {};
};

class quackBehavior{
public:
	virtual void quack() {};
};

class flyWithWing : public flyBehavior{
public:
	void fly(){
		std::cout << "fly away" << std::endl;
	}
};

class noFly : public flyBehavior{
public:
	void fly(){
		std::cout << "can't fly" << std::endl;
	}
};

class sayQuack : public quackBehavior{
	void quack(){
		std::cout << "quack!" << std::endl;
	}
};

class sayQQuack : public quackBehavior{
	void quack(){
		std::cout << "qquack!" << std::endl;
	}
};

class duck{
public:
	flyBehavior *flyInstance;
	quackBehavior *quackInstance;
	duck(){
		delete flyInstance;
		delete quackInstance;
	}
	void fly(){
		flyInstance->fly();
	}

	void quack(){
		quackInstance->quack();
	}
	
	void swim(){
		std::cout << "do swin" << std::endl;
	}
};

class mallardDuck : public duck{
public:
	mallardDuck(){
		flyInstance = new flyWithWing();
		quackInstance = new sayQuack();
	}
};

class rubberDuck : public duck{
public:
	rubberDuck(){
		flyInstance = new noFly();
		quackInstance = new sayQQuack();
	}
};

int main(){
	using namespace std;
	mallardDuck *a = new mallardDuck;
	rubberDuck *b = new rubberDuck;
	cout << "mallard duck do" << endl;
	a->quack();
	a->fly();
	a->swim();

	cout << "rubber duck do" << endl;
	b->quack();
	b->fly();
	b->swim();

	delete a;
}
