# pasha_anc_co

```
#define FREE = 0
#define BUZY = 1
#define EXIT = 2
#define pointType unsigned char

class Point {
public:
	Point(pointType type, int layer = 0);

private:
	pointType type;
	float x, y;
	int layer;
};

class Pin {
public:
	Pin(int x,int y);
	
private:
	int x, y;
};

class Map {
public:
	void takePoint(int x, int y, int z);
	bool isTakenPoint(int x, int y, int z);
	void thin();

	void takePoint(int x, int y, int z) {
	
	}
	bool isTakenPoint(int x, int y, int z);
	
private:
	std::vector<Point*> map;
};
```
