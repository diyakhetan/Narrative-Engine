#pragma once
#include <string>
#include<cmath>
#include "collision.h"
#include "renderdata.h"
#include<filesystem>


enum ObjectType
{
	type_Platform,
    type_Light,
    type_Player,
    type_Interactable,
    type_MovementPoint
};


// Function to get the path to the current executable
inline std::wstring GetExePath() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return std::wstring(buffer).substr(0, pos);
}

class GameObject
{
public:
    ObjectType objectType;
    std::shared_ptr<ObjectRenderData> renderData;//stores
    std::string name;//name of the game object
    ObjectTransform transform;//transform data of the gameobject
    BoxCollider collider;
    GameObject() {
        // Set default values or perform initialization if needed
        name = "nothing selected";
    }

	GameObject(const std::string name) : name(name)//test constructor
	{
        std::wstring exePath = GetExePath();
        std::filesystem::path shadersPath = std::filesystem::path(exePath) / "Shaders"; // Assuming Shaders folder is in the same directory as the executable
        // Set the path to the shaders
        std::filesystem::current_path(shadersPath);
    	auto path = std::filesystem::current_path();
        std::cout << path;
        renderData = std::make_shared<Cube>();// new Plane();
        const Material mat(glm::vec4(1, 1, 1, 1));
        renderData->SetMaterial(mat);
    	Shader s("defaultShader.vert","defaultShader.frag");
    	renderData->material.setShader(s);
        std::cout << "\n GAME OBJECT CREATED \n";
	}

    GameObject(const std::string name, ObjectTransform transformData) :name(name), transform(transformData)
    {
        std::wstring exePath = GetExePath();
        std::filesystem::path shadersPath = std::filesystem::path(exePath) / "Shaders"; // Assuming Shaders folder is in the same directory as the executable

        // Set the path to the shaders
        std::filesystem::current_path(shadersPath);
        auto path = std::filesystem::current_path();

        std::cout << path;
    	renderData = std::make_shared<Cube>();// new Plane();
        const Material mat(glm::vec4(1, 1, 1, 1));
        renderData->SetMaterial(mat);
        Shader s("defaultShader.vert", "colorShader.frag");
        renderData->material.setShader(s);

        std::cout << "\n GAME OBJECT CREATED \n";
    }
    GameObject(const std::string name, ObjectTransform transformData, glm::vec3 color) :name(name), transform(transformData)
    {
        std::wstring exePath = GetExePath();
        std::filesystem::path shadersPath = std::filesystem::path(exePath) / "Shaders"; // Assuming Shaders folder is in the same directory as the executable

        // Set the path to the shaders
        std::filesystem::current_path(shadersPath);
        auto path = std::filesystem::current_path();

        std::cout << path;
        renderData = std::make_shared<Cube>();// new Plane();
        const Material mat(glm::vec4(1, 1, 1, 1));
        renderData->SetMaterial(mat);
        Shader s("defaultShader.vert", "colorShader.frag");
        renderData->material.setShader(s);
        renderData->material.color = glm::vec4(color,1);
        std::cout << "\n GAME OBJECT CREATED \n";
    }
    virtual ~GameObject() = default;  // Virtual destructor
    bool operator==(const GameObject& other) const {
        return name == other.name;
    }
};


class Platform:public GameObject
{
public:
    Platform() {
        // Set default values or perform initialization if needed
        name = "nothing selected";
    }

    Platform(const std::string name)
    {
        GameObject::name = name;
        objectType = ObjectType::type_Platform;
        std::wstring exePath = GetExePath();
        std::filesystem::path shadersPath = std::filesystem::path(exePath) / "Shaders"; // Assuming Shaders folder is in the same directory as the executable
        // Set the path to the shaders
        std::filesystem::current_path(shadersPath);
        auto path = std::filesystem::current_path();
        std::cout << path;
        renderData = std::make_shared<Cube>();// new Plane();
        const Material mat(glm::vec4(1, 1, 1, 1));
        renderData->SetMaterial(mat);
        Shader s("defaultShader.vert", "defaultShaderwithlighting.frag");
        renderData->material.setShader(s);
        std::cout << "\n GAME OBJECT CREATED \n";
    }

    Platform(const std::string name, ObjectTransform transformData) 
    {
        objectType = ObjectType::type_Platform;

        GameObject::name = name;
        transform = transformData;

        std::wstring exePath = GetExePath();
        std::filesystem::path shadersPath = std::filesystem::path(exePath) / "Shaders"; // Assuming Shaders folder is in the same directory as the executable

        // Set the path to the shaders
        std::filesystem::current_path(shadersPath);
        auto path = std::filesystem::current_path();

        std::cout << path;
        renderData = std::make_shared<Cube>();// new Plane();
        const Material mat(glm::vec4(1, 1, 1, 1));
        renderData->SetMaterial(mat);
        Shader s("defaultShader.vert", "defaultShaderwithlighting.frag");
        renderData->material.setShader(s);

        std::cout << "\n GAME OBJECT CREATED \n";
    }
    Platform(const std::string name, ObjectTransform transformData, glm::vec3 color) 
    {

        GameObject::name = name;
        transform = transformData;
        objectType = ObjectType::type_Platform;

        std::wstring exePath = GetExePath();
        std::filesystem::path shadersPath = std::filesystem::path(exePath) / "Shaders"; // Assuming Shaders folder is in the same directory as the executable

        // Set the path to the shaders
        std::filesystem::current_path(shadersPath);
        auto path = std::filesystem::current_path();

        std::cout << path;
        renderData = std::make_shared<Cube>();// new Plane();
        const Material mat(glm::vec4(1, 1, 1, 1));
        renderData->SetMaterial(mat);
        Shader s("defaultShader.vert", "defaultShaderwithlighting.frag");
        renderData->material.setShader(s);
        renderData->material.color = glm::vec4(color, 1);
        std::cout << "\n GAME OBJECT CREATED \n";
    }

    
};

class Light:public GameObject
{
private:
    float intensity=0.5;

public:
    Light() {
        // Set default values or perform initialization if needed
        name = "nothing selected";
    }

    Light(const std::string name)
    {
        GameObject::name = name;
        objectType = ObjectType::type_Light;

        std::wstring exePath = GetExePath();
        std::filesystem::path shadersPath = std::filesystem::path(exePath) / "Shaders"; // Assuming Shaders folder is in the same directory as the executable
        // Set the path to the shaders
        std::filesystem::current_path(shadersPath);
        auto path = std::filesystem::current_path();
        std::cout << path;
        renderData = std::make_shared<Cube>();// new Plane();
        const Material mat(glm::vec4(1, 1, 1, 1));
        renderData->SetMaterial(mat);
        Shader s("defaultShader.vert", "lightfragmentshader.frag");
        renderData->material.setShader(s);
        std::cout << "\n GAME OBJECT CREATED \n";
    }

    Light(const std::string name, ObjectTransform transformData) 
    {
        GameObject::name = name;
        objectType = ObjectType::type_Light;

        GameObject::transform = transformData;
        std::wstring exePath = GetExePath();
        std::filesystem::path shadersPath = std::filesystem::path(exePath) / "Shaders"; // Assuming Shaders folder is in the same directory as the executable

        // Set the path to the shaders
        std::filesystem::current_path(shadersPath);
        auto path = std::filesystem::current_path();

        std::cout << path;
        renderData = std::make_shared<Cube>();// new Plane();
        const Material mat(glm::vec4(1, 1, 1, 1));
        renderData->SetMaterial(mat);
        Shader s("defaultShader.vert", "lightfragmentshader.frag");
        renderData->material.setShader(s);

        std::cout << "\n GAME OBJECT CREATED \n";
    }
    Light(const std::string name, ObjectTransform transformData, glm::vec3 color)
	{
        GameObject::name = name;
        GameObject::transform = transformData;
        objectType = ObjectType::type_Light;

        std::wstring exePath = GetExePath();
        std::filesystem::path shadersPath = std::filesystem::path(exePath) / "Shaders"; // Assuming Shaders folder is in the same directory as the executable

        // Set the path to the shaders
        std::filesystem::current_path(shadersPath);
        auto path = std::filesystem::current_path();

        std::cout << path;
        renderData = std::make_shared<Cube>();// new Plane();
        const Material mat(glm::vec4(1, 1, 1, 1));
        renderData->SetMaterial(mat);
        Shader s("defaultShader.vert", "lightfragmentshader.frag");
        renderData->material.setShader(s);
        renderData->material.color = glm::vec4(color, 1);
        std::cout << "\n GAME OBJECT CREATED \n";
    }

	void setIntensity(float newIntensity)
    {
        intensity = newIntensity;
    }

	float getIntensity() const { return intensity; }
};

class Player: public GameObject
{
private:

public:
    Player() {
        // Set default values or perform initialization if needed
        name = "nothing selected";
    }

    Player(const std::string name)
    {
        GameObject::name = name;
        objectType = ObjectType::type_Player;

        std::wstring exePath = GetExePath();
        std::filesystem::path shadersPath = std::filesystem::path(exePath) / "Shaders"; // Assuming Shaders folder is in the same directory as the executable
        // Set the path to the shaders
        std::filesystem::current_path(shadersPath);
        auto path = std::filesystem::current_path();
        std::cout << path;
        renderData = std::make_shared<Cube>();// new Plane();
        const Material mat(glm::vec4(1, 1, 1, 1));
        renderData->SetMaterial(mat);
        Shader s("defaultShader.vert", "defaultShaderwithlighting.frag");
        renderData->material.setShader(s);
        std::cout << "\n GAME OBJECT CREATED \n";
    }

    Player(const std::string name, ObjectTransform transformData)
    {
        GameObject::name = name;
        objectType = ObjectType::type_Player;

        GameObject::transform = transformData;
        std::wstring exePath = GetExePath();
        std::filesystem::path shadersPath = std::filesystem::path(exePath) / "Shaders"; // Assuming Shaders folder is in the same directory as the executable

        // Set the path to the shaders
        std::filesystem::current_path(shadersPath);
        auto path = std::filesystem::current_path();

        std::cout << path;
        renderData = std::make_shared<Cube>();// new Plane();
        const Material mat(glm::vec4(1, 1, 1, 1));
        renderData->SetMaterial(mat);
        Shader s("defaultShader.vert", "defaultShaderwithlighting.frag");
        renderData->material.setShader(s);

        std::cout << "\n GAME OBJECT CREATED \n";
    }
    Player(const std::string name, ObjectTransform transformData, glm::vec3 color)
    {
        GameObject::name = name;
        GameObject::transform = transformData;
        objectType = ObjectType::type_Player;

        std::wstring exePath = GetExePath();
        std::filesystem::path shadersPath = std::filesystem::path(exePath) / "Shaders"; // Assuming Shaders folder is in the same directory as the executable

        // Set the path to the shaders
        std::filesystem::current_path(shadersPath);
        auto path = std::filesystem::current_path();

        std::cout << path;
        renderData = std::make_shared<Cube>();// new Plane();
        const Material mat(glm::vec4(1, 1, 1, 1));
        renderData->SetMaterial(mat);
        Shader s("defaultShader.vert", "defaultShaderwithlighting.frag");
        renderData->material.setShader(s);
        renderData->material.color = glm::vec4(color, 1);
        std::cout << "\n GAME OBJECT CREATED \n";
    }
    
    void changePosition(glm::vec3 newPos)
    {
        transform.translation = newPos;
        transform.CalculateModel();
    }
};


enum EventTime
{
	Enter,
    Exit
};
enum EventType
{
	TextBox,
    Print,
    Inventory,
    SceneChange
};

struct Item
{
public:
    std::string name;
    int count = 1;
};

class ConditionalEventData
{
private:
    Item item;
public:
    ConditionalEventData()
    {
        item.name = "";
        item.count = 0;
    }
    ConditionalEventData(std::string name, int count)
    {
        setItem(name, count);
    }
    void setItem(std::string itemName, int n)
    {
        item.name = itemName;
        item.count = n;
    }
    bool CheckConditionSatisfied()
    {
	    
    }
    void setCount(int n) { item.count = n; }
    Item getItem() { return item; }
};

class Inventory
{
private:
    std::vector<std::string> itemNames;
    std::vector<Item> itemsHeldCurrently;
public:
    std::vector<std::string>& getItemNames() { return itemNames; }
    std::vector<Item>& getCurrentInventory() { return itemsHeldCurrently; }
    void clearData()
    {
        itemsHeldCurrently.clear();
        itemNames.clear();
    }
    void clearPlayerInventory()
    {
        itemsHeldCurrently.clear();
    }
    void addItemToList(const std::string i)
    {
        itemNames.push_back(i);
    }
    void removeLastItemFromList()
    {
        if (!itemNames.empty())
        {
            itemNames.pop_back();
        }
    }
    void addItemToInventory(Item i)
    {

        for (auto& item : itemsHeldCurrently)
        {
            if (item.name == i.name)
            {
                item.count += i.count;

                if (item.count < 0)
                {
                    item.count = 0;
                }
                return;
            }
        }
        itemsHeldCurrently.push_back(i);
    }
    void removeItemFromInventory(Item i)
    {
        for (auto it = itemsHeldCurrently.begin(); it != itemsHeldCurrently.end(); ++it)
        {
            if (it->name == i.name)
            {
                it->count -= i.count;
                if (it->count <= 0)
                {
                    itemsHeldCurrently.erase(it);
                }
                break;
            }
        }
    }
    bool checkForItem(std::string itemname, int count)
    {
        for (auto& item : itemsHeldCurrently)
        {
            if (item.name == itemname && item.count >= count)
            {
                return true;
            }
        }
        return false;
    }

} manager_Inventory;


class Event
{
private:
    EventTime eventTime=Enter;
    std::string eventName;
    EventType eventType;

    //allow user to create conditions if they want
    bool isConditional=false;

public:
    ConditionalEventData conditionalEventData;

    Event() {}
    Event(std::string ename, EventType etype, EventTime etime)
    {
        setEventType(etype);
        setEventName(ename);
        setEventTime(etime);
    }
    void setEventTime(EventTime type)
    {
        eventTime = type;
    }
    void setEventName(std::string name)
    {
        eventName = name;
    }
    void setEventType(EventType type)
    {
        eventType = type;
    }
    virtual void doThing(){}
    void runEvent()
    {
        if (isConditional)
        {
            conditionalDoThing();
        }
        else
            doThing();
    }
	void conditionalDoThing()
    {
	    if(manager_Inventory.checkForItem(conditionalEventData.getItem().name,conditionalEventData.getItem().count))
	    {
            doThing();
	    }
    }
    std::string getName() { return eventName; }
    EventTime getTime() { return eventTime; }
    EventType getType() { return eventType; }
    void setConditional(bool con) { isConditional = con; }
    bool getIsConditional() { return isConditional; }
};


class MovementPoint:public GameObject
{
private:

public:
    //array of events
    std::vector<std::shared_ptr<Event>> events;
    void deleteSpecificEvent()
    {
	    
    }
   

    MovementPoint() {
        // Set default values or perform initialization if needed
        name = "nothing selected";
    }
    MovementPoint(const std::string name)
    {
        GameObject::name = name;
        objectType = ObjectType::type_MovementPoint;

        std::wstring exePath = GetExePath();
        std::filesystem::path shadersPath = std::filesystem::path(exePath) / "Shaders"; // Assuming Shaders folder is in the same directory as the executable
        // Set the path to the shaders
        std::filesystem::current_path(shadersPath);
        auto path = std::filesystem::current_path();
        std::cout << path;
        renderData = std::make_shared<Cube>();// new Plane();


        const Material mat(glm::vec4(1, 1, 1, 1));
        renderData->SetMaterial(mat);
        Shader s("defaultShader.vert", "colorShader.frag");
        renderData->material.setShader(s);
        transform.scale = glm::vec3(0.2);

    	std::cout << "\n GAME OBJECT CREATED \n";

    }
    MovementPoint(const std::string name, ObjectTransform transformData)
    {
        GameObject::name = name;
        objectType = ObjectType::type_MovementPoint;

        GameObject::transform = transformData;
        std::wstring exePath = GetExePath();
        std::filesystem::path shadersPath = std::filesystem::path(exePath) / "Shaders"; // Assuming Shaders folder is in the same directory as the executable

        // Set the path to the shaders
        std::filesystem::current_path(shadersPath);
        auto path = std::filesystem::current_path();

        std::cout << path;
        renderData = std::make_shared<Cube>();// new Plane();
        const Material mat(glm::vec4(1, 1, 1, 1));
        renderData->SetMaterial(mat);
        Shader s("defaultShader.vert", "colorShader.frag");
        renderData->material.setShader(s);
        transform.scale = glm::vec3(0.2);

        std::cout << "\n GAME OBJECT CREATED \n";
    }
    MovementPoint(const std::string name, ObjectTransform transformData, glm::vec3 color)
    {
        GameObject::name = name;
        GameObject::transform = transformData;
        objectType = ObjectType::type_MovementPoint;

        std::wstring exePath = GetExePath();
        std::filesystem::path shadersPath = std::filesystem::path(exePath) / "Shaders"; // Assuming Shaders folder is in the same directory as the executable

        // Set the path to the shaders
        std::filesystem::current_path(shadersPath);
        auto path = std::filesystem::current_path();

        std::cout << path;
        renderData = std::make_shared<Cube>();// new Plane();
        const Material mat(glm::vec4(1, 1, 1, 1));
        renderData->SetMaterial(mat);
        Shader s("defaultShader.vert", "colorShader.frag");
        renderData->material.setShader(s);
        renderData->material.color = glm::vec4(color, 1);
        transform.scale = glm::vec3(0.2);

    	std::cout << "\n GAME OBJECT CREATED \n";
    }

};

class CameraObject:public GameObject
{
	
};



template<typename T>
bool ray_collision_impl(glm::vec3 origin, glm::vec3 dir, const std::vector<std::shared_ptr<T>>& objects, std::shared_ptr<T>& obj)
{
    float totaldist = 0;
    glm::vec3 current_pos = origin;
    for (int i = 0; i < MAX_RAY_ITERATIONS; i++)
    {
        float min_dist = std::numeric_limits<float>::infinity();
        double calc_distance = 0;
        for (const auto& object : objects)
        {
            if (object->collider.CollisionTest(current_pos, object->transform.translation, object->transform.rotation, object->transform.scale))
            {
                obj = object;
                return true;
            }
            calc_distance = object->collider.sdBox(current_pos, object->transform.translation, object->transform.rotation, object->transform.scale);
            if (calc_distance < min_dist)
            {
                min_dist = calc_distance;
            }
        }
        totaldist += min_dist;
        current_pos = origin + dir * totaldist;
        if (totaldist > 100000)
        {
            return false;
        }
    }
    return false;
}

bool ray_collision(glm::vec3 origin, glm::vec3 dir, const std::vector<std::shared_ptr<GameObject>>& gameObjects, std::shared_ptr<GameObject>& obj)
{
    return ray_collision_impl(origin, dir, gameObjects, obj);
}

bool ray_collision(glm::vec3 origin, glm::vec3 dir, const std::vector<std::shared_ptr<MovementPoint>>& movementPoints, std::shared_ptr<MovementPoint>& obj)
{
    return ray_collision_impl(origin, dir, movementPoints, obj);
}