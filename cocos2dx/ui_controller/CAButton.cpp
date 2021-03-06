//
//  CAButton.cpp
//  CrossApp
//
//  Created by Li Yuanfeng on 14-3-23.
//  Copyright (c) 2014 http://www.9miao.com All rights reserved.
//

#include "CAButton.h"
#include "sprite_nodes/CAScale9ImageView.h"
#include "sprite_nodes/CAView.h"
#include "touch_dispatcher/CCTouch.h"
#include "support/CCPointExtension.h"
#include "cocoa/CCSet.h"
#include "label_nodes/CCLabelTTF.h"
#define PLAYSOUND 

NS_CC_BEGIN

CAButton::CAButton(CAButtonType buttonType)
:m_bAllowsSelected(false)
,m_bSelected(false)
,m_textTag("")
,m_closeTapSound(false)
,m_bTouchClick(false)
,m_color(ccWHITE)
,m_IsRehisterTouchDispatcher(false)
,m_eButtonType(buttonType)
,m_sTitleFontName("fonts/arial.ttf")
,m_pImageView(NULL)
,m_pLabel(NULL)
,m_pSpriteNormal(NULL)
,m_pSpriteHighlighted(NULL)
,m_pSpriteDisabled(NULL)
,m_pSpriteSelected(NULL)
,m_tSpriteNPoint(CCPointZero)
,m_tSpriteHPoint(CCPointZero)
,m_tSpriteDPoint(CCPointZero)
,m_tSpriteSPoint(CCPointZero)
{
    for (int i=0; i<CAControlStateAll; i++)
    {
        m_pImage[i] = NULL;
        m_sTitle[i] = "";
        m_sImageColor[i] = ccWHITE;
        m_sTitleColor[i] = ccBLACK;
    }
    
    m_pImageView = new CAImageView();
    m_pImageView->init();
    m_pLabel = new CCLabelTTF();
    m_pLabel->initWithString("", m_sTitleFontName.c_str(), 20);
}

CAButton::~CAButton(void)
{
    CC_SAFE_RELEASE_NULL(m_pImageView);
    CC_SAFE_RELEASE_NULL(m_pLabel);
    CC_SAFE_RELEASE_NULL(m_pSpriteNormal);
    CC_SAFE_RELEASE_NULL(m_pSpriteHighlighted);
    CC_SAFE_RELEASE_NULL(m_pSpriteDisabled);
    CC_SAFE_RELEASE_NULL(m_pSpriteSelected);
}

void CAButton::onExitTransitionDidStart()
{
    CAView::onExitTransitionDidStart();
}

void CAButton::onEnterTransitionDidFinish()
{
    CAView::onEnterTransitionDidFinish();
    
    this->updateWithPoint();
    this->setControlState(m_eControlState);
}

CAButton* CAButton::create(CAButtonType buttonType)
{
    
    CAButton* btn = new CAButton(buttonType);
    
    if (btn && btn->init())
    {
        btn->autorelease();
        return btn;
    }
    
    CC_SAFE_DELETE(btn);
    return NULL;
}

CAButton* CAButton::createWithFrame(const CCRect& rect, CAButtonType buttonType)
{

    CAButton* btn = new CAButton(buttonType);
    
    if (btn && btn->initWithFrame(rect))
    {
        btn->autorelease();
        return btn;
    }
    
    CC_SAFE_DELETE(btn);
    return NULL;
}

CAButton* CAButton::createWithCenter(const CCRect& rect, CAButtonType buttonType)
{
    
    CAButton* btn = new CAButton(buttonType);
    
    if (btn && btn->initWithCenter(rect))
    {
        btn->autorelease();
        return btn;
    }
    
    CC_SAFE_DELETE(btn);
    return NULL;
}

bool CAButton::initWithFrame(const CCRect& rect)
{
    if (!CAButton::init())
    {
        return false;
    }

    this->setFrame(rect);
    return true;
}

bool CAButton::initWithCenter(const CCRect& rect)
{
    if (!CAButton::init())
    {
        return false;
    }
    
    this->setCenter(rect);
    return true;
}

bool CAButton::init()
{
    if (!CAView::init())
    {
        return false;
    }
    
    switch (m_eButtonType)
    {
        case CAButtonTypeSquareRect:
            this->setBackGroundViewSquareRect();
            break;
        case CAButtonTypeRoundedRect:
            this->setBackGroundViewRoundedRect();
            break;
        case CAButtonTypeRounded3DRect:
            this->setBackGroundViewRounded3DRect();
            break;
        default:
            break;
    }
    
    this->insertSubview(m_pImageView, 1);
    this->insertSubview(m_pLabel, 1);
    
    return true;
}

void CAButton::setBackGroundViewSquareRect()
{
    const char* fileName[CAControlStateAll] =
    {
        "btn_square_normal.png",
        "btn_square_highlighted.png",
        "btn_square_disabled.png",
        "btn_square_selected.png"
    };
    
    ccColor3B color[CAControlStateAll] =
    {
        ccc3(11, 106, 255),
        ccc3(11, 106, 255),
        ccc3(255, 255, 255),
        ccc3(138, 138, 138)
    };
    
    for (int i=0; i<CAControlStateAll; i++)
    {
        CAImage* image = CAImage::create(fileName[i]);
        CAScale9ImageView* bg = CAScale9ImageView::createWithImage(image);
        this->setBackGroundViewForState((CAControlState)i, bg);
        m_sTitleColor[i] = color[i];
    }
}

void CAButton::setBackGroundViewRoundedRect()
{
    const char* fileName[CAControlStateAll] =
    {
        "btn_rounded_normal.png",
        "btn_rounded_highlighted.png",
        "btn_rounded_disabled.png",
        "btn_rounded_selected.png"
    };
    
    ccColor3B color[CAControlStateAll] =
    {
        ccc3(11, 106, 255),
        ccc3(11, 106, 255),
        ccc3(255, 255, 255),
        ccc3(138, 138, 138)
    };
    
    for (int i=0; i<CAControlStateAll; i++)
    {
        CAImage* image = CAImage::create(fileName[i]);
        CAScale9ImageView* bg = CAScale9ImageView::createWithImage(image);
        this->setBackGroundViewForState((CAControlState)i, bg);
        m_sTitleColor[i] = color[i];
    }
}

void CAButton::setBackGroundViewRounded3DRect()
{
    const char* fileName[CAControlStateAll] =
    {
        "btn_rounded3D_normal.png",
        "btn_rounded3D_highlighted.png",
        "btn_rounded3D_disabled.png",
        "btn_rounded3D_selected.png"
    };
    
    ccColor3B color[CAControlStateAll] =
    {
        ccc3(255, 255, 255),
        ccc3(0, 41, 57),
        ccc3(127, 127, 127),
        ccc3(255, 255, 255)
    };
    
    for (int i=0; i<CAControlStateAll; i++)
    {
        CAImage* image = CAImage::create(fileName[i]);
        CAScale9ImageView* bg = CAScale9ImageView::createWithImage(image);
        this->setBackGroundViewForState((CAControlState)i, bg);
        m_sTitleColor[i] = color[i];
    }
}

void CAButton::setBackGroundViewForState(CAControlState controlState, CAView *var)
{
    CAControl::setBackGroundViewForState(controlState, var);
    do
    {
        CC_BREAK_IF(var == NULL);
        
        if (this->getBounds().equals(CCRectZero))
        {
            this->setBounds(CCRect(0, 0, var->getFrame().size.width, var->getFrame().size.height));
        }
        
        this->updateWithPoint();
        this->updateWithPreferredSize();
    }
    while (0);
}

void CAButton::setImageForState(CAControlState controlState, CAImage* var)
{
    if (controlState == CAControlStateAll)
    {
        for (int i=0; i<CAControlStateAll; i++)
        {
            this->setImageForState((CAControlState)i, var);
        }
        return;
    }
    
    if (m_pImage[controlState] != var)
    {
        CC_SAFE_RETAIN(var);
        CC_SAFE_RELEASE(m_pImage[controlState]);
        m_pImage[controlState] = var;
    }
}

void CAButton::setTitleForState(CAControlState controlState, std::string var)
{
    if (controlState == CAControlStateAll)
    {
        for (int i=0; i<CAControlStateAll; i++)
        {
            this->setTitleForState((CAControlState)i, var);
        }
        return;
    }
    
    if (m_sTitle[controlState] != var)
    {
        m_sTitle[controlState] = var;
    }
}

void CAButton::setImageColorForState(CAControlState controlState, ccColor3B var)
{
    m_sImageColor[controlState] = var;
}

void CAButton::setTitleColorForState(CAControlState controlState, ccColor3B var)
{
    m_sTitleColor[controlState] = var;
}

void CAButton::setTitleFontName(std::string var)
{
    if (m_sTitleFontName.compare(var))
    {
        m_sTitleFontName = var;
        m_pLabel->setFontName(m_sTitleFontName.c_str());
    }
}

void CAButton::updateWithPreferredSize()
{
    for (int i=0; i<CAControlStateAll; i++)
    {
        CC_CONTINUE_IF(m_pBackGroundView[i] == NULL);
        CC_CONTINUE_IF(this->getBounds().equals(m_pBackGroundView[i]->getBounds()));
        
        if (CAScale9ImageView* _var = dynamic_cast<CAScale9ImageView*>(m_pBackGroundView[i]))
        {
            _var->setPreferredSize(m_obContentSize);
        }
        else
        {
            m_pBackGroundView[i]->setFrame(this->getBounds());
        }
    }
    
    m_pLabel->setFontSize(this->getBounds().size.height * 0.667f);
}

bool CAButton::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint point = pTouch->getLocation();
    point = this->convertToNodeSpace(point);

    do
    {
        CC_BREAK_IF(!this->isVisible());
        CC_BREAK_IF(!m_bTouchEnabled);
        CC_BREAK_IF(m_eControlState != CAControlStateNormal && m_eControlState != CAControlStateSelected);
        CC_BREAK_IF(!getBounds().containsPoint(point));
        
        return this->setTouchBegin(point);
    }
    while (0);
    
    return false;
}

void CAButton::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint point = pTouch->getLocation();
    point = this->convertToNodeSpace(point);
    
    if (!this->isTouchClick()) return;
    
    if (getBounds().containsPoint(point))
    {
        this->setTouchMoved(point);
        this->setControlState(CAControlStateHighlighted);
    }
    else
    {
        this->setTouchMovedOutSide(point);
        if (m_bAllowsSelected && m_bSelected)
        {
            this->setControlState(CAControlStateSelected);
        }
        else
        {
            this->setControlState(CAControlStateNormal);
        }
    }
}

void CAButton::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint point = pTouch->getLocation();
    point = this->convertToNodeSpace(point);

    if (!this->isTouchClick())
        return;
    
    this->setTouchUpSide(point);
    
    if (getBounds().containsPoint(point))
    {
        this->setTouchUpInSide(point);
    }

    do
    {
        CC_BREAK_IF(this->getControlState() != CAControlStateHighlighted);
        
        if (m_bAllowsSelected)
        {
            if (m_bSelected)
            {
                m_bSelected = false;
                this->setControlState(CAControlStateNormal);
            }
            else
            {
                m_bSelected = true;
                this->setControlState(CAControlStateSelected);
            }
        }
        else
        {
            this->setControlState(CAControlStateNormal);
        }
    }
    while (0);
}

void CAButton::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bAllowsSelected && m_bSelected)
    {
        this->setControlState(CAControlStateSelected);
    }
    else
    {
        this->setControlState(CAControlStateNormal);
    }
}

void CAButton::setControlState(CAControlState var)
{
    CAControl::setControlState(var);

    if (m_eControlState == CAControlStateSelected)
    {
        m_bSelected = true;
    }
    else if(m_eControlState != CAControlStateHighlighted)
    {
        m_bSelected = false;
    }
    
    do
    {
        CC_BREAK_IF(m_pSpriteNormal);
        CC_BREAK_IF(m_pSpriteHighlighted);
        CC_BREAK_IF(m_pSpriteDisabled);
        CC_BREAK_IF(m_pSpriteSelected);
        
        CAImage* image = NULL;
        std::string title = "";
        CCRect imageViewCenter = CCRectZero;
        CCRect rect = CCRectZero;
        CCPoint labelCenterOrigin = CCPointZero;
        float labelSize = 0;
        
        image = m_pImage[m_eControlState];
        title = m_sTitle[m_eControlState];
        
        if (image == NULL)
        {
            image = this->isSelected() ? m_pImage[CAControlStateSelected] : m_pImage[CAControlStateNormal];
        }
        
        if (strcmp(title.c_str(), "") == 0)
        {
            title = this->isSelected() ? m_sTitle[CAControlStateSelected] : m_sTitle[CAControlStateNormal];
        }
        
        if (image && title.compare("") == 0)
        {
            CCSize size = this->getBounds().size;
            CCSize iSize = image->getContentSize();
            float scaleX = size.width / iSize.width * 0.75f;
            float scaleY = size.height / iSize.height * 0.75f;
            float scale = MIN(scaleX, scaleY);
            scale = MIN(scale, 1.0f);
            iSize = ccpMult(iSize, scale);
            
            imageViewCenter.origin = size / 2;
            imageViewCenter.size = iSize;
        }
        else if (image == NULL && title.compare("") != 0)
        {
            labelSize = this->getBounds().size.height * 0.667f;
            labelCenterOrigin = this->getBounds().size / 2 ;
        }
        else if (image && title.compare("") != 0)
        {
            CCSize size = this->getBounds().size;
            CCSize iSize = image->getContentSize();
            float scaleX = size.width / iSize.width * 0.4f;
            float scaleY = size.height / iSize.height * 0.4f;
            float scale = MIN(scaleX, scaleY);
            scale = MIN(scale, 1.0f);
            iSize = ccpMult(iSize, scale);
            
            imageViewCenter.size = iSize;
            imageViewCenter.origin.x = size.width / 2;
            imageViewCenter.origin.y = size.height * 0.35f;

            labelSize = size.height * 0.3f;
            labelCenterOrigin.x = size.width / 2;
            labelCenterOrigin.y = size.height * 0.8f;
        }
        
        if (image)
        {
            rect.size = image->getContentSize();
        }
        
        if (image != m_pImageView->getImage())
        {
            m_pImageView->setImage(image);
            m_pImageView->setImageRect(rect);
        }
        m_pImageView->setCenter(imageViewCenter);
        
        m_pImageView->setColor(m_sImageColor[m_eControlState]);
        m_pLabel->setColor(m_sTitleColor[m_eControlState]);
        
        if (strcmp(title.c_str(), m_pLabel->getString().c_str()))
        {
            m_pLabel->setFontSize(labelSize);
            m_pLabel->setString(title.c_str());
            
            if (m_pLabel->getFrame().size.width > this->getBounds().size.width * 0.8f)
            {
                float scale = (this->getBounds().size.width * 0.8f) / m_pLabel->getFrame().size.width;
                m_pLabel->setScale(scale);
            }
        }
        m_pLabel->setCenterOrigin(labelCenterOrigin);
    }
    while (0);
    
    /*****************************/
    
    this->removeSubview(m_pSpriteNormal);
    this->removeSubview(m_pSpriteHighlighted);
    this->removeSubview(m_pSpriteDisabled);
    this->removeSubview(m_pSpriteSelected);
    
    switch (m_eControlState)
    {
        case CAControlStateNormal:
        {
            if (m_pSpriteNormal)
            {
                this->addSubview(m_pSpriteNormal);
            }
            break;
        }
        case CAControlStateHighlighted:
        {
            if (m_pSpriteHighlighted)
            {
                this->addSubview(m_pSpriteHighlighted);
            }
            else if (m_pSpriteNormal)
            {
                this->addSubview(m_pSpriteNormal);
            }
            break;
        }
        case CAControlStateDisabled:
        {
            if (m_pSpriteDisabled)
            {
                this->addSubview(m_pSpriteDisabled);
            }
            else if (m_pSpriteNormal)
            {
                this->addSubview(m_pSpriteNormal);
            }
            break;
        }
        case CAControlStateSelected:
        {
            if (m_pSpriteSelected)
            {
                this->addSubview(m_pSpriteSelected);
            }
            else if (m_pSpriteNormal)
            {
                this->addSubview(m_pSpriteNormal);
            }
            break;
        }
        default:
            break;
    }
    
    /*****************************/
}

void CAButton::interruptTouchState()
{
	do
	{
		CC_BREAK_IF(m_bTouchClick == false);
		m_bTouchClick = false;
		if (m_bAllowsSelected && m_bSelected)
        {
            this->setControlState(CAControlStateSelected);
        }
        else
        {
            this->setControlState(CAControlStateNormal);
        }

	} while (0);
}

bool CAButton::setTouchBegin(CCPoint point)
{
	m_bTouchClick = true;

    if (m_pTarget[CAControlEventTouchDown] && m_selTouch[CAControlEventTouchDown])
    {
		m_bTouchClick = ((CCObject *)m_pTarget[CAControlEventTouchDown]->*m_selTouch[CAControlEventTouchDown])(this, point);
    }
    
	if (m_bTouchClick)
	{
		this->setControlState(CAControlStateHighlighted);
	}

	return m_bTouchClick;
}

void CAButton::setTouchUpInSide(CCPoint point)
{
    if (m_pTarget[CAControlEventTouchUpInSide] && m_selTouch[CAControlEventTouchUpInSide])
    {
        ((CCObject *)m_pTarget[CAControlEventTouchUpInSide]->*m_selTouch[CAControlEventTouchUpInSide])(this,point);
    }
}

void CAButton::setTouchUpSide(CCPoint point)
{
    if (m_pTarget[CAControlEventTouchUpSide] && m_selTouch[CAControlEventTouchUpSide])
    {
        ((CCObject *)m_pTarget[CAControlEventTouchUpSide]->*m_selTouch[CAControlEventTouchUpSide])(this,point);
    }
}

void CAButton::setTouchMoved(cocos2d::CCPoint point)
{
    if (m_pTarget[CAControlEventTouchMoved] && m_selTouch[CAControlEventTouchMoved])
    {
        ((CCObject *)m_pTarget[CAControlEventTouchMoved]->*m_selTouch[CAControlEventTouchMoved])(this,point);
    }
}

void CAButton::setTouchMovedOutSide(cocos2d::CCPoint point)
{
    if (m_pTarget[CAControlEventTouchMovedOutSide] && m_selTouch[CAControlEventTouchMovedOutSide])
    {
        ((CCObject *)m_pTarget[CAControlEventTouchMovedOutSide]->*m_selTouch[CAControlEventTouchMovedOutSide])(this,point);
    }
}

bool CAButton::isTextTagEqual(const char *text)
{
    return (m_textTag.compare(text)==0);
}

void CAButton::setContentSize(const CCSize & var)
{
    CAControl::setContentSize(var);
    
    this->updateWithPoint();
    
    this->updateWithPreferredSize();
    
    this->setControlState(m_eControlState);
}

void CAButton::setOpacity(GLubyte opacity)
{
    CAView::setOpacity(opacity);
    
    if (this->getSubviews())
    {
        for (int i=0; i<this->getSubviews()->count(); i++)
        {
            CAView* view=(CAView*)this->getSubviews()->objectAtIndex(i);
            
            if (CCRGBAProtocol* _children=dynamic_cast<CCRGBAProtocol*>(view))
            {
                _children->setOpacity(opacity);
            }
        }
    }
}

void CAButton::setColor(const ccColor3B &color3){
    
    m_color=color3;
    
    if (this->getSubviews())
    {
        for (int i=0; i<this->getSubviews()->count(); i++)
        {
            CAView* view=(CAView*)this->getSubviews()->objectAtIndex(i);
            
            if (CCRGBAProtocol* _children=dynamic_cast<CCRGBAProtocol*>(view))
            {
                _children->setColor(color3);
            }
        }
    }
}

ccColor3B& CAButton::getColor(){
    
    return m_color;
}



void CAButton::setView(CAControlState controlState, CAView* var)
{
    if (!var)
        return;
    
    var->setAnchorPoint(CCPoint(0.5f, 0.5f));
    
    CCPoint point = m_obContentSize/2;
    
    this->setView(controlState, var, point);
}

void CAButton::setView(CAControlState controlState, CAView* var, CCPoint point)
{
    if (!var)
        return;
    
    var->setAnchorPoint(CCPoint(0.5f, 0.5f));
    var->setPosition(point);
    var->retain();
    
    CCPoint cPoint = m_obContentSize/2;
    
    if (controlState == CAControlStateNormal)
    {
        this->removeSubview(m_pSpriteNormal);
        CC_SAFE_DELETE(m_pSpriteNormal);
        
        if (!cPoint.equals(point))
        {
            m_tSpriteNPoint = point;
        }
        else
        {
            m_tSpriteNPoint = CCPointZero;
        }
        
        m_pSpriteNormal = var;
        
        return;
    }
    else if (controlState == CAControlStateHighlighted)
    {
        this->removeSubview(m_pSpriteHighlighted);
        CC_SAFE_DELETE(m_pSpriteHighlighted);
        
        if (!cPoint.equals(point))
        {
            m_tSpriteHPoint = point;
        }
        else
        {
            m_tSpriteHPoint = CCPointZero;
        }
        
        m_pSpriteHighlighted = var;
    }
    else if (controlState == CAControlStateDisabled)
    {
        this->removeSubview(m_pSpriteDisabled);
        CC_SAFE_DELETE(m_pSpriteDisabled);
        
        if (!cPoint.equals(point))
        {
            m_tSpriteDPoint = point;
        }
        else
        {
            m_tSpriteDPoint = CCPointZero;
        }
        
        m_pSpriteDisabled = var;
    }
    else if (controlState == CAControlStateSelected)
    {
        this->removeSubview(m_pSpriteSelected);
        CC_SAFE_DELETE(m_pSpriteSelected);
        
        if (!cPoint.equals(point))
        {
            m_tSpriteSPoint = point;
        }
        else
        {
            m_tSpriteSPoint = CCPointZero;
        }
        
        m_pSpriteSelected = var;
    }
}

CAView* CAButton::getView(CAControlState controlState)
{
    switch (controlState)
    {
        case CAControlStateNormal:
            return m_pSpriteNormal;
            break;
        case CAControlStateHighlighted:
            return m_pSpriteHighlighted;
            break;
        case CAControlStateDisabled:
            return m_pSpriteDisabled;
            break;
        case CAControlStateSelected:
            return m_pSpriteSelected;
            break;
        default:
            return NULL;
            break;
    }
}

void CAButton::updateWithPoint()
{
    
    CCPoint point = m_obContentSize/2;
    
    if (m_pSpriteNormal)
    {
        if (m_tSpriteNPoint.equals(CCPointZero))
        {
            m_pSpriteNormal->setAnchorPoint(CCPoint(0.5f, 0.5f));
            m_pSpriteNormal->setPosition(point);
        }
        else
        {
            m_pSpriteNormal->setPosition(m_tSpriteNPoint);
        }
    }
    
    if (m_pSpriteHighlighted)
    {
        if (m_tSpriteHPoint.equals(CCPointZero))
        {
            m_pSpriteHighlighted->setAnchorPoint(CCPoint(0.5f, 0.5f));
            m_pSpriteHighlighted->setPosition(point);
        }
        else
        {
            m_pSpriteHighlighted->setPosition(m_tSpriteHPoint);
        }
    }
    
    if (m_pSpriteDisabled)
    {
        if (m_tSpriteDPoint.equals(CCPointZero))
        {
            m_pSpriteDisabled->setAnchorPoint(CCPoint(0.5f, 0.5f));
            m_pSpriteDisabled->setPosition(point);
        }
        else
        {
            m_pSpriteDisabled->setPosition(m_tSpriteDPoint);
        }
    }
    
    if (m_pSpriteSelected)
    {
        if (m_tSpriteSPoint.equals(CCPointZero))
        {
            m_pSpriteSelected->setAnchorPoint(CCPoint(0.5f, 0.5f));
            m_pSpriteSelected->setPosition(point);
        }
        else
        {
            m_pSpriteSelected->setPosition(m_tSpriteSPoint);
        }
    }
}

NS_CC_END