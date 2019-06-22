# MFC Aircraft-Battle 飞机大战

### 一、课设题目

以windows编程、事件驱动的程序设计为基础，使用MFC 类库实现一个带有GUI界面的飞机大战程序。

实现基本功能：

- 战场背景，飞机，武器等的图形化绘制。
- 可以操控战机移动，发射武器。
- 飞机可以通过碰撞或被武器击中而损毁。 

其他功能：

- 随机产生补给包，可以为战机提升生命值。
- 战机升级，战机分数达到一定阶段后会进行升级，发射更密集和多方向的子弹，共有三种子弹模式。

### 二、基本框架

飞机大战游戏的实现基于MFC文档-视结构框架，它将数据的处理和显示分开来。

文档对象用于管理和维护数据，包括保存数据、取出数据以及修改数据等操作，在数据被修改以后，文档可以通知其对应的所有视图更新显示。

视图对象将文档中的数据可视化，负责从文档对象中取出数据显示给用户，并接受用户的输入和编辑，将数据的改变反映给文档对象。视图充当了文档和用户之间媒介的角色。

框架用来管理文档和视图，框架窗口是应用程序的主窗口，应用程序执行时会先创建一个最顶层的框架窗口。视图窗口是没有菜单和边界的子窗口，它必须包含在框架窗口中，即置于框架窗口的客户区内。

文档模板中存放了与文档、视图和框架相关的信息。应用程序通过文档模板创建文档对象、框架窗口对象和视图对象。另外，文档、视图和框架之间的关系也是由文档模板来管理的。

飞机大战游戏实现过程中，主要涉及到的是文档对象对数据的管理和视图对象的可视化，具体来说，文档对象负责游戏开始前一些历史数据的读入和游戏结束后数据的存储，视图对象负责游戏界面的绘制，飞机、炮弹位置的变化以及键盘、鼠标按键的响应等操作。

在底层实现上，设计如下几个类：

`CGameObject` ：派生自 `CObject` 类，它是所有游戏对象的父类，所有游戏对象都继承自它

`CPlane` ：派生自 `CGameObject`  类，它是游戏对象中飞机类对象的父类，本方战机类和敌机类都继承自它

`MyPlane` ：派生自 `CPlane` 类，描述本方战机对象

`CEnemy` ：派生自 `CPlane` 类，描述敌方战机对象

`CBullet` ：派生自 `CGameObject` 类，描述子弹/炮弹对象

`CSupply` ：派生自 `CGameObject` 类，描述补给包对象

它们之间的组织关系如下图所示：

![](C:\Users\tf\Desktop\大三下\高级程序设计\课程设计二\图片1.png)

在界面上，共有三种类型的界面：开始界面、游戏界面、结束界面。他们之间的逻辑关系如下图所示：

![](C:\Users\tf\Desktop\大三下\高级程序设计\课程设计二\图片2.png)

程序初始运行时进入开始界面，进行一些提示信息的显示，玩家按下空格键或鼠标左键开始游戏，进入游戏界面，游戏结束后进入结束界面，进行一些总结信息的显示，并提示玩家是否继续游戏，若是，则回到游戏界面重新开始，否则退出程序。

### 三、具体实现

#### 数据结构

`CGameObject` 类的定义如下：

```C++
class CGameObject : public CObject {
protected:
	CPoint  mPoint;		// 游戏对象的位置
public:
	CGameObject(int x = 0, int y = 0);
	virtual ~CGameObject();
	virtual BOOL Draw(CDC* pDC, BOOL bPause) = 0;	// 绘制对象
	virtual CRect GetRect() = 0; 					// 获得物体矩形区域
	CPoint GetPoint(); 								// 获得左上角坐标
	void SetPoint(int x, int y);					// 设置坐标
protected:
	static BOOL LoadImage(CImageList& imageList, UINT bmpID, COLORREF crMask, int cx, int cy, int nInitial); 	// 加载该游戏对象对应的图像
};
```

`CGameObject` 类是所有游戏物体对象的基类，飞机、子弹、补给包类都继承自它。它包含一个游戏对象位置数据，以及对于游戏对象的绘制和获得位置、获得区域、设置位置操作。此外还有一个加载游戏对象图像的接口，值得注意的是，由于图像对象是共有数据，因此同一个游戏对象类只需要加载一份，所以使用静态方法。

`CPlane` 类的定义如下：

```C++
class CPlane : public CGameObject {
protected:
	int hp; 		// 生命值
	int maxHp; 		// 生命值上限
	int damage; 	// 伤害值
	int speedX; 	// 横向速度
	int speedY; 	// 纵向速度
public:
	CPlane();
	CPlane(int _hp, int _damage, int _speedX, int _speedY);
	int getHp() const; 		// 获取生命值
	int getSpeedX() const; 	// 获取横向速度
	int getSpeedY() const; 	// 获取纵向速度
	int getDamage() const;	// 获取伤害值
	void decreaseHp(int x);	// 减少生命
	void increaseHp(int x);	// 增加生命
	bool isAlive() const; 	// 是否存活
};
```

`CPlane` 类描述飞机类对象，它是本方战机类和敌方战机类的基类，它包含飞机类基本的成员对象：生命值、伤害值、速度等，在公有成员函数里提供一些获取这些值和对这些值操作的对外接口，此外提供一个判断该飞机是否存活（即生命值大于0）的接口函数。

`CMyPlane` 类的定义如下：

```C++
class CMyPlane : public CPlane {
private:
	static CImageList images; 			// 战机图像
public:
	CMyPlane();							// 构造函数
	BOOL Draw(CDC* pDC, BOOL bPause);	// 绘制函数
	static BOOL LoadImage();			// 加载图像
	CRect GetRect();					// 获取矩形区域
};
```

`CMyplane` 类描述了本方战机对象，与静态成员函数 `LoadImage` 相对应地，它有一个静态成员变量 `images` ，负责存储战机的图像列表，由于战机升级等原因，战机会有多种图像，因此把它们存储为图像列表类型 `CImageList` 。此外重写基类中的 `Draw` 、`LoadImage` 、`GetRect` 方法，分别定制绘制、加载本方战机图像以及获取图像在屏幕上的矩形区域。在 `Draw` 函数绘制战机时，直接将战机图像绘制在 `mPoint` 坐标点上即可。

`CEnemy` 类的定义如下：

```C++
class CEnemy : public CPlane {
private:
	int score;							// 敌机分数
	int index; 							// 敌机种类
	static CImageList enemyImages; 		// 敌机图像
public:
	CEnemy(int w, int h, int i); 		// 构造函数
	int getScore() const; 				// 获取敌机分数
	int getIndex() const; 				// 获取敌机种类
	CRect GetRect(); 					// 获取矩形区域
	BOOL Draw(CDC* pDC, BOOL bPause); 	// 绘制函数
	static BOOL LoadImage(); 			// 加载敌机图像
};
```

`CEnemy` 类描述了敌方战机类，和 `CMyPlane` 类类似，它也有静态成员变量 `enemyImages` 存储敌机图像列表，以及相应的静态成员函数 `LoadImage` 负责加载敌机图像，以及重写基类方法，此外，它还有一个成员变量 `score` ，存储本方战机击毁该敌机可获得的分数，以及一些相应的对外接口。在构造函数中，需要随机初始化敌机的初始坐标和速度，利用随机函数生成。与本方战机不同的是，本方战机的移动受玩家手动控制，而地方战机的移动需要自动移动，因此在绘制时，需要将坐标 `mPoint` 加上两个方向移动速度，再进行绘制。

`CBullet` 类的定义如下：

```C++
class CBullet :	public CGameObject {
private:
	bool fromMe; 	// 是否是本方战机子弹
	int speedX; 	// 横向速度
	int speedY;		// 纵向速度
	int damage;		// 伤害值
	int index;		// 子弹种类
	static CImageList myBulletImages;		// 战机子弹图像
	static CImageList enemyBulletImages;	// 敌机子弹图像
public:
	CBullet(int x, int y, int d, int sx, int sy, bool fm, int i);
	int getSpeedX() const;  			// 获取横向速度
	int getSpeedY() const;				// 获取纵向速度
	int getDamage() const;				// 获取伤害值
	bool getFromMe() const; 			// 获取是否本机子弹
	CRect GetRect();     				// 获取矩形区域
	BOOL Draw(CDC* pDC, BOOL bPause); 	// 绘制函数
	static BOOL LoadImage(); 			// 加载子弹图像
};
```

`CBullet` 类描述了子弹对象，子弹分为本方战机子弹和敌方战机子弹，本方战机子弹向上飞行，敌方战机子弹向下飞行，`damage` 变量描述了该子弹的伤害值，通常该值与发射该子弹的战机的伤害值相同，即用发射该子弹的 `damage` 变量值来初始化子弹类的 `damage` 变量。由于战机子弹和敌机子弹不同，所以需要存储两个子弹战机图像列表。其他部分与前述的 `CEnemy` 类类似，不再赘述。

`CSupply` 类的定义如下：

```C++
class CSupply : public CGameObject {
private:
	int windowWidth; 			// 屏幕宽度
	int windowHeight; 			// 屏幕高度
	int speedX; 				// 横向速度
	int speedY; 				// 纵向速度
	int hp;						// 补给生命值
	static CImageList images; 	// 图像列表
public:
	CSupply(int WINDOWS_WIDTH, int WINDOWS_HEIGHT);
	BOOL Draw(CDC* pDC, BOOL bPause); 	// 绘制函数
	int getHp() const; 					// 获取补给生命值
	static BOOL LoadImage(); 			// 加载补给包图像
	CRect GetRect(); 					// 获取矩形区域
};
```

`CSupply` 类描述了补给包对象，它包含补给包的移动速度和能够补给的生命值，此外，和子弹类不同的是，子弹在移动出屏幕后直接消亡，而补给包除非被本方战机吃到，否则一直会在屏幕中移动，不会消亡，若遇到屏幕边界，则向相反方向继续移动，因此需要存储屏幕的宽度和高度。在公有函数中提供一些接口并重写基类方法。

#### 文档-视结构

在程序运行时，在Doc类中加载数据，进行一些初始化工作，在View类中进行大量的可视化操作。

首先绘制开始界面，显示一些提示信息，监听鼠标和键盘事件，若获得空格键按下或鼠标左键点击事件消息，则进入游戏界面，机械能绘制游戏场景以及游戏对象图像，通过计时器每隔一段时间随机产生敌机，敌机随机发射子弹，随机产生补给包，此外监听键盘和鼠标事件，若空格键按下或鼠标左键点击，则本方战机发射子弹。

每个时刻遍历子弹列表，判断：

- 是否有子弹移动到屏幕外，若是，则将该子弹销毁。
- 是否有本方子弹与敌机区域重叠，若是，则说明该子弹击中敌机，敌机生命值降低，若敌机生命值减至0，则该敌机被击毁，将该对象消亡。
- 是否有敌机子弹与本方战机区域重叠，若是，则说明该子弹击中本方战机，本方战机生命值降低，若本方战机生命值减至0，则本方战机被击毁，游戏结束，进入结束界面。
- 是否有本方战机子弹和敌机子弹区域重叠，若是，则将两个子弹对象消亡。

每个时刻遍历补给包列表，判断是否有补给包与本方战机区域重合，若是，则说明本方战机吃到补给包，本方战机生命值增加，补给包对象消亡。

每个时刻遍历敌机列表，判断：

- 是否有敌机与本方战机区域重叠，若是，则说明本方战机与敌机发生碰撞，本方战机减少大量生命值，敌机对象消亡，若本方那个战机生命值减至0，则本方战机被击毁，游戏结束，进入结束界面。
- 是否有敌机位置移动到屏幕外，若是，则直接将该敌机对象消亡。

在结束界面，显示最终玩家分数，若分数超过历史最高，则将其保存，更新游戏记录。在屏幕上显示游戏信息，若玩家选择继续游戏，则回到游戏界面重新开始，否则退出游戏。

### 四、运行结果

开始界面：

![](C:\Users\tf\Desktop\大三下\高级程序设计\课程设计二\1.png)

游戏界面：

![](C:\Users\tf\Desktop\大三下\高级程序设计\课程设计二\2.png)

结束界面：

![](C:\Users\tf\Desktop\大三下\高级程序设计\课程设计二\3.png)