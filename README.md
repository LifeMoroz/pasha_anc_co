# pasha_anc_co

```
class Point {
private:
	int x, y, z;
};

class Pin {
private:
	int x, y, z;
public:
	Pin(int x,int y, int z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

class Map {
private:
	bool*** map; // std::vector;
public:
	void takePoint(Point point);
	bool isTakenPoint(Point point);
	void thin();
};
```
