class Animal
{
public:
    Animal(std::string thisName)
    {
        myName = thisName;
    }
    virtual void speak() const = 0;

    virtual std::string moveAction() const
    {
        return "walk";
    }

    std::string name() const
    {
        return myName;
    }

    virtual ~Animal() {}
private:
    std::string myName;
};

class Cat: public Animal
{
public:
    Cat(std::string thisName) : Animal(thisName) { myName = thisName; }

    virtual void speak() const
    {
        std::cout << "Meow";
    }

    ~Cat()
    {
        std::cout << "Destroying " << myName << " the cat" << std::endl;
    }
private:
    std::string myName;
};

class Pig : public Animal
{
public:
    Pig(std::string thisName, int weight): Animal(thisName)
    {
        myName = thisName;
        myWeight = weight;
    }

    virtual void speak() const
    {
        if (myWeight > 160)
            std::cout << "Grunt";
        else
            std::cout << "Oink";
    }

    ~Pig()
    {
        std::cout << "Destroying " << myName << " the pig" << std::endl;
    }

private:
    std::string myName;
    int myWeight;
};

class Duck : public Animal
{
public:
    Duck(std::string thisName) : Animal(thisName) { myName = thisName; }

    virtual void speak() const
    {
        std::cout << "Quack";
    }

    virtual std::string moveAction() const
    {
        return "swim";
    }

    ~Duck()
    {
        std::cout << "Destroying " << myName << " the duck" << std::endl;
    }
private:
    std::string myName;
};