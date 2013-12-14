#include "bplayer.h"
#include "BGun.h"

HGE* BPlayer::hge = NULL;

// constructor
BPlayer::BPlayer(hgeVector b_vPPosition, hgeVector b_vPVelocity)
{
	// get interface to HGE
	hge = hgeCreate(HGE_VERSION);

	// create an animation with 4 frames and 4 FPS
	b_tPTexture = hge->Texture_Load("img/Spritesheet_64x29.png");
	b_aPSprite	= new hgeAnimation(b_tPTexture, 8, 8, 0, 0, 64, 29);
	
	// set player position and velocity
	this->b_vPPosition = b_vPPosition;
	this->b_vPVelocity = b_vPVelocity;

	// sets the hotspot: 
	// anchor point which is center for scaling, rotation and positionning
	b_aPSprite->SetHotSpot(32, 14.5);
	b_aPSprite->Play();

	b_fPSpeed		= 0.25f; 
	b_fPFriction	= 0.95f;

	// create the default weapon
	pWeapon = new BGun("Gun", 0, 10);
}

//destructor
BPlayer::~BPlayer(void)
{
	hge->Texture_Free(b_tPTexture);
	delete b_aPSprite;

	hge->Release();
}

// movement calcluation
bool BPlayer::OnLoop(float delta)
{
	// velocity * friction && position * velocity
	b_vPVelocity.x *= b_fPFriction;
	b_vPVelocity.y *= b_fPFriction;

	b_vPPosition.x += b_vPVelocity.x;
	b_vPPosition.y += b_vPVelocity.y;

	// make the player moveable using the AWSD & ARROW keys while making sure not to cross screen boundaries
	// M_PI is 3.1415..
	if(hge->Input_GetKeyState(HGEK_A) || hge->Input_GetKeyState(HGEK_LEFT) && b_vPPosition.x > 32) 
		b_vPVelocity.x -= (b_fPSpeed * M_PI) / 2;
	if(hge->Input_GetKeyState(HGEK_D) || hge->Input_GetKeyState(HGEK_RIGHT) && b_vPPosition.x < 800) 
		b_vPVelocity.x += (b_fPSpeed * M_PI) / 2;
	if(hge->Input_GetKeyState(HGEK_W) || hge->Input_GetKeyState(HGEK_UP) && b_vPPosition.y > 0) 
		b_vPVelocity.y -= (b_fPSpeed * M_PI) / 2;
	if(hge->Input_GetKeyState(HGEK_S) || hge->Input_GetKeyState(HGEK_DOWN) && b_vPPosition.y < 600) 
		b_vPVelocity.y += (b_fPSpeed * M_PI) / 2;

	// make sure to keep the player in check inside the screen
	if(b_vPPosition.x > 800) { 
		b_vPPosition.x -= 1; 
		b_vPVelocity.x	= -b_vPVelocity.x; };
	if(b_vPPosition.x < 0) { 
		b_vPPosition.x += 1; 
		b_vPVelocity.x	= -b_vPVelocity.x; };
	if(b_vPPosition.y < 0) { 
		b_vPPosition.y += 1; 
		b_vPVelocity.y	= -b_vPVelocity.y; };
	if(b_vPPosition.y > 600) { 
		b_vPPosition.y -= 1; 
		b_vPVelocity.y	= -b_vPVelocity.y; };

	// update animation and bounding box
	b_aPSprite->Update(delta);

	b_aPSprite->GetBoundingBox(b_vPPosition.x, b_vPPosition.y, &b_rPBoudingBox);

	// false otherwise the game will stop
	return false;
}

// render
void BPlayer::OnRender(void)
{
	b_aPSprite->Render(b_vPPosition.x, b_vPPosition.y);
}

// getters and setters
void BPlayer::setVelocity(hgeVector velocity)
{
	this->b_vPVelocity = velocity;
}

void BPlayer::setPosition(hgeVector position)
{
	this->b_vPPosition = position;
}

hgeRect BPlayer::getBoundingBox(void)
{
	return b_rPBoudingBox;
}

hgeVector BPlayer::getPosition(void)
{
	return b_vPPosition;
}