﻿#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init())
    {
        return false;
    }

	srand((int)time(NULL));
    
	// 윈도우 크기를 구한다
	winSize = Director::getInstance()->getWinSize();

	// 이미지의 텍스쳐를 구한다
	texture = Director::getInstance()->getTextureCache()->addImage("blocks.png");

	// 월드 생성
	if (this->createBox2dWorld(true))
	{
		this->schedule(schedule_selector(HelloWorld::tick));
	}

    return true;
}

bool HelloWorld::createBox2dWorld(bool debug)
{
	// 월드 생성 시작------------------------------


	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);
	
	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);
	
	// 디버그 드로잉 설정

	if (debug)
	{
		// 적색 : 현재 물리 운동을 하는 것
		// 회색 : 현재 물리 운동량이 없는 것
		m_debugDraw = new GLESDebugDraw(PTM_RATIO);
		_world->SetDebugDraw(m_debugDraw);

		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;

		m_debugDraw->SetFlags(flags);
	}

	// bodydef에 좌표를 설정한다
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	// 월드에 boduydef의 정보(좌표)로 body를 만든다
	b2Body *groundBody = _world->CreateBody(&groundBodyDef);

	// 가장자리(테두리) 경계선을 그릴 수 있는 모양의 객체를 만든다.
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	// edge 모양의 객체에 Set(점1, 점2)로 선을 만든다.
	// 그리고 바디(groundbody)에 모양(groundEdge)을 고정시킨다.
	// 만일 객체간의 거리가 10m가 넘으면 오차가 생길 수 있다.

	// 아래쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);
	// 왼쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);
	// 위쪽
	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO), b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);
	// 오른쪽
	groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	// 월드 생성 끝  -------------------------------------------------------

	// 추가----------------------------------------------------------------

	// staticBody sprite를 추가한다.
	Sprite* sprite1 = Sprite::createWithTexture(texture, Rect(0, 0, 64, 64));
	sprite1->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(sprite1);

	// bodydef를 만들고 속성들을 지정한다
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(winSize.width / 2 / PTM_RATIO, winSize.height / 2 / PTM_RATIO);
	bodyDef.userData = sprite1;
	b2Body* body1 = _world->CreateBody(&bodyDef);

	// body에 적용할 물리 속성용 body의 모양을 만든다
	b2PolygonShape staticBox;
	// body의 크기 지정 - 상자의 크기에서 가운데 위치를 지정한다.
	staticBox.SetAsBox((sprite1->getContentSize().width / 2) / PTM_RATIO, (sprite1->getContentSize().height / 2) / PTM_RATIO);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;
	fixtureDef.density = 1.0f;

	body1->CreateFixture(&fixtureDef);


	// kinematicBody sprite를 추가한다.
	Sprite* sprite2 = Sprite::createWithTexture(texture, Rect(0, 0, 64, 32));
	sprite2->setPosition(Vec2(0,100));
	this->addChild(sprite2);

	// bodydef를 만들고 속성들을 지정한다
	b2BodyDef bodyDef2;
	bodyDef2.type = b2_kinematicBody;
	bodyDef2.position.Set(0, 100 / PTM_RATIO);
	bodyDef2.linearVelocity = b2Vec2(1, 0);
	bodyDef2.userData = sprite2;
	b2Body* body2 = _world->CreateBody(&bodyDef2);

	// body에 적용할 물리 속성용 body의 모양을 만든다
	b2PolygonShape kinematicBox;
	// body의 크기 지정 - 상자의 크기에서 가운데 위치를 지정한다.
	staticBox.SetAsBox((sprite2->getContentSize().width / 2) / PTM_RATIO, (sprite2->getContentSize().height / 2) / PTM_RATIO);
	b2FixtureDef fixtureDef2;
	fixtureDef2.shape = &kinematicBox;
	fixtureDef2.density = 1.0f;

	body1->CreateFixture(&fixtureDef2);

	return true;
}

HelloWorld::~HelloWorld()
{
	delete _world;
	_world = NULL;
}

void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);

	_customCmd.init(_globalZOrder, transform, flags);
	_customCmd.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&_customCmd);
}

void HelloWorld::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	_world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void HelloWorld::onEnter() 
{
	Layer::onEnter();

	// 싱글 터치 모드로 터치리스너 등록
	auto listener = EventListenerTouchOneByOne::create();

	// Swallow touches only avaailiable in OneByOne mode.
	// 핸들링 된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미이다
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

	// The priority of the touch listener is basd on the draw order of sprite
	// 터치리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() 
{
	_eventDispatcher->removeAllEventListeners();

	Layer::onExit();
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) 
{
	auto touchPoint = touch->getLocation();

	// 터치된 지점에 새로운 물리 객체의 바디와 해당 스프라이트를 추가한다.
	addNewSpriteAtPosition(touchPoint);

	return true;
}

void HelloWorld::tick(float t) 
{

	// 물리적 위치를 이영해 그래픽 위치를 갱신한다.

	// velocityIterations : body들을 정상적으로 이동시키기 위해 필요한 충돌들을 반복적으로 계산
	// positionIterations ; 조인트 분리와 겹침 현상을 줄이기 위해 바디의 위치를 반복적으로 적용
	// 값이 클수록 정확한 연산이 가능하지만 성능이 떨어진다

	// 프로젝트 생성 시 기본값
	int velocityIterations = 8;
	int positionIterations = 3;

	// Step : 물리 세계를 시뮬레이션한다
	_world->Step(t, velocityIterations, positionIterations);

	// 모든 물리 객체들은  linkedList에 저장되어 참조해 볼 수 있게 구현돼 있다.
	// 만들어진 객체 만큼 루프를 돌리면서 바다에 붙인 스프라이트를 여기서 제어한다.
	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			Sprite* spriteData = (Sprite*)b->GetUserData();
			spriteData->setPosition(Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}

		if (b->GetType() == b2_kinematicBody)
		{
			b2Vec2 v = b->GetPosition();
			if (v.x * PTM_RATIO > winSize.width)
				b->SetLinearVelocity(b2Vec2(-1.0f, 0));
			else if(v.x < 0)
				b->SetLinearVelocity(b2Vec2(1.0f, 0));
		}
	}
}

void HelloWorld::addNewSpriteAtPosition(Vec2 location)
{
	int num = rand() % 3;

	// bodyDef 만들고 속성들을 지정한다.
	b2BodyDef bodydef;
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
	bodydef.userData = nullptr;

	// 월드에 bodydef의 정보로 body를 만든다.
	b2Body* body = _world->CreateBody(&bodydef);
	
	if (num == 0)
	{
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(0.8f, 0.8f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 0;

		body->CreateFixture(&fixtureDef);
	}
	else if (num == 1)
	{
		b2PolygonShape dynamicBox;
		b2Vec2 tri[3];

		tri[0].x = -.5;
		tri[0].y = 0;

		tri[1].x = .5;
		tri[1].y = 0;

		tri[2].x = 0;
		tri[2].y = 1;

		dynamicBox.Set(tri, 3);


		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 1.0f;

		body->CreateFixture(&fixtureDef);
	}
	else
	{
		b2CircleShape dynamicCircle;
		dynamicCircle.m_radius = 1;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicCircle;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.2f;
		fixtureDef.restitution = 1;

		body->CreateFixture(&fixtureDef);
	}

}
