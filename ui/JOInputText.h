//
//  joUtils.h
//  joUtils
//
//  Created by James on 15/3/12.
//  Copyright (c) 2015??? dream. All rights reserved.
//
#ifndef __JO_INPUT_TEXT_H__
#define __JO_INPUT_TEXT_H__

#include "utils/JOMacro.h"

#include "cocos2d.h"
USING_NS_CC;

NS_JOFW_BEGIN

class JO_DLL JOInputText : public TextFieldTTF
{
public:
	
    enum INPUT_EVENT
    {
        INPUT_EVENT_ATTACH = 1,
        INPUT_EVENT_DETACH,
        INPUT_EVENT_INSERT_BEGIN,
        INPUT_EVENT_INSERT_END,
        INPUT_EVENT_DELETE,
        INPUT_EVENT_KEYBOARDSHOW,
        INPUT_EVENT_KEYBOARDHIDE
    };
    JOInputText();
    static JOInputText * create(const std::string& placeholder, const std::string& fontName, float fontSize);
    bool init(const std::string& placeholder, const std::string& fontName, float fontSize);
    
    void setInputEventCallback(LUA_FUNCTION eventCallback);
protected:
    virtual bool canAttachWithIME();
    virtual bool canDetachWithIME();

    virtual void didAttachWithIME();
    virtual void didDetachWithIME();
    
    virtual void insertText(const char * text, size_t len);

    virtual void deleteBackward();
    
    //////////////////////////////////////////////////////////////////////////
    // keyboard show/hide notification
    //////////////////////////////////////////////////////////////////////////
    virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info);
    virtual void keyboardDidShow(IMEKeyboardNotificationInfo& info);
    virtual void keyboardWillHide(IMEKeyboardNotificationInfo& info);
    virtual void keyboardDidHide(IMEKeyboardNotificationInfo& info);
    
private:
    LUA_FUNCTION _eventCallback;
};

NS_JOFW_END
#endif /* __JO_INPUT_TEXT_H__ */
