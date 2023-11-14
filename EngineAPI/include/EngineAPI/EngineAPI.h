#pragma once


namespace CloneAPI
{
#define LOG_DEBUG(Category, Message) CLONE_DEBUG(Category, Message)
#define LOG_INFO(Category, Message)  CLONE_INFO(Category, Message) 
#define LOG_WARN(Category, Message)  CLONE_WARN(Category, Message) 
#define LOG_ERROR(Category, Message) CLONE_ERROR(Category, Message)
#define LOG_FATAL(Category, Message) CLONE_FATAL(Category, Message)
}
