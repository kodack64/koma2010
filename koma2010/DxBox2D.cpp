#include "dx8.h"
#include "box2d_data.h"

b2Body* CDirectX::b2CreateBox(float x,float y,float wid,float hei,float ldump,float rdump,float density,float friction,float rest,bool dynamics,bool sensor,b2State* st){
	b2BodyDef bodyDef;
	if(dynamics){
		bodyDef.type = b2_dynamicBody;
	}
	else{
		bodyDef.type = b2_staticBody;
	}
	bodyDef.position.Set(x*PIXtoM,y*PIXtoM);
	bodyDef.angularDamping=rdump;
	bodyDef.linearDamping=ldump;
	bodyDef.userData=st;
	b2Body* body = world->CreateBody(&bodyDef);
	b2PolygonShape staticBox;
	staticBox.SetAsBox(wid*PIXtoM,hei*PIXtoM);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution=rest;
	fixtureDef.isSensor=sensor;
	body->CreateFixture(&fixtureDef);
	return body;
}
b2Body* CDirectX::b2CreateCircle(float x,float y,float r,float ldump,float rdump,float density,float friction,float rest,bool dynamics,bool sensor,b2State* st){
	b2BodyDef bodyDef;
	if(dynamics){
		bodyDef.type = b2_dynamicBody;
	}
	else{
		bodyDef.type = b2_staticBody;
	}
	bodyDef.angularDamping=rdump;
	bodyDef.linearDamping=ldump;
	bodyDef.position.Set(x*PIXtoM,y*PIXtoM);
	bodyDef.userData=st;
	b2Body* body = world->CreateBody(&bodyDef);
	b2CircleShape circle;
	circle.m_radius = r*PIXtoM;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution=rest;
	fixtureDef.isSensor=sensor;
	body->CreateFixture(&fixtureDef);
	return body;
}
b2Body* CDirectX::b2CreatePolygon(float x,float y,b2Vec2* poly,int vernum,float ldump,float rdump,float density,float friction,float rest,bool dynamics,bool sensor,b2State* st){
	b2BodyDef bodyDef;
	if(dynamics){
		bodyDef.type = b2_dynamicBody;
	}
	else{
		bodyDef.type = b2_staticBody;
	}
	bodyDef.angularDamping=rdump;
	bodyDef.linearDamping=ldump;
	bodyDef.position.Set(x*PIXtoM,y*PIXtoM);
	bodyDef.userData=st;
	b2Body* body = world->CreateBody(&bodyDef);
	b2PolygonShape polygon;
	for(int x=0;x<vernum;x++){
		poly[x].x*=PIXtoM;
		poly[x].y*=PIXtoM;
	}
	polygon.Set(poly,vernum);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygon;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution=rest;
	fixtureDef.isSensor=sensor;
	body->CreateFixture(&fixtureDef);
	return body;
}