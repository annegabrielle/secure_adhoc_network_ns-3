/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2006,2007 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#include "log.h"

#ifdef NS3_LOG_ENABLE

#include <list>
#include <utility>
#include <iostream>
#include "assert.h"
#include "ns3/core-config.h"
#include "fatal-error.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

namespace ns3 {

LogTimePrinter g_logTimePrinter = 0;
LogNodePrinter g_logNodePrinter = 0;

typedef std::list<std::pair <std::string, LogComponent *> > ComponentList;
typedef std::list<std::pair <std::string, LogComponent *> >::iterator ComponentListI;

static class PrintList
{
public:
  PrintList ();
} g_printList;

static 
ComponentList *GetComponentList (void)
{
  static ComponentList components;
  return &components;
}



PrintList::PrintList ()
{
#ifdef HAVE_GETENV
  char *envVar = getenv("NS_LOG");
  if (envVar == 0)
    {
      return;
    }
  std::string env = envVar;
  std::string::size_type cur = 0;
  std::string::size_type next = 0;
  while (next != std::string::npos)
    {
      next = env.find_first_of (":", cur);
      std::string tmp = std::string (env, cur, next-cur);
      if (tmp == "print-list")
        {
          LogComponentPrintList ();
          exit (0);
          break;
        }
      cur = next + 1;
    }
#endif  
}


LogComponent::LogComponent (char const * name)
  : m_levels (0), m_name (name)
{
  EnvVarCheck (name);

  ComponentList *components = GetComponentList ();
  for (ComponentListI i = components->begin ();
       i != components->end ();
       i++)
    {
      if (i->first == name)
        {
          NS_FATAL_ERROR ("Log component \""<<name<<"\" has already been registered once.");
        }
    }
  components->push_back (std::make_pair (name, this));
}

void
LogComponent::EnvVarCheck (char const * name)
{
#ifdef HAVE_GETENV
  char *envVar = getenv("NS_LOG");
  if (envVar == 0)
    {
      return;
    }
  std::string env = envVar;
  std::string myName = name;

  std::string::size_type cur = 0;
  std::string::size_type next = 0;
  while (next != std::string::npos)
    {
      next = env.find_first_of (":", cur);
      std::string tmp = std::string (env, cur, next-cur);
      std::string::size_type equal = tmp.find ("=");
      std::string component;
      if (equal == std::string::npos)
        {
          component = tmp;
          if (component == myName || component == "*")
            {
              int level = LOG_ALL | LOG_PREFIX_TIME | LOG_PREFIX_FUNC | LOG_PREFIX_NODE;
              Enable ((enum LogLevel)level);
              return;
            }
        }
      else
        {
          component = tmp.substr (0, equal);
          if (component == myName || component == "*")
            {
              int level = 0;
              std::string::size_type cur_lev;
              std::string::size_type next_lev = equal;
              do
                {
                  cur_lev = next_lev + 1;
                  next_lev = tmp.find ("|", cur_lev);
                  std::string lev = tmp.substr (cur_lev, next_lev - cur_lev);
                  if (lev == "error")
                    {
                      level |= LOG_ERROR;
                    }
                  else if (lev == "warn")
                    {
                      level |= LOG_WARN;
                    }
                  else if (lev == "debug")
                    {
                      level |= LOG_DEBUG;
                    }
                  else if (lev == "info")
                    {
                      level |= LOG_INFO;
                    }
                  else if (lev == "function")
                    {
                      level |= LOG_FUNCTION;
                    }
                  else if (lev == "logic")
                    {
                      level |= LOG_LOGIC;
                    }
                  else if (lev == "all")
                    {
                      level |= LOG_ALL;
                    }
                  else if (lev == "prefix_func")
                    {
                      level |= LOG_PREFIX_FUNC;
                    }
                  else if (lev == "prefix_time")
                    {
                      level |= LOG_PREFIX_TIME;
                    }
                  else if (lev == "prefix_node")
                    {
                      level |= LOG_PREFIX_NODE;
                    }
                  else if (lev == "level_error")
                    {
                      level |= LOG_LEVEL_ERROR;
                    }
                  else if (lev == "level_warn")
                    {
                      level |= LOG_LEVEL_WARN;
                    }
                  else if (lev == "level_debug")
                    {
                      level |= LOG_LEVEL_DEBUG;
                    }
                  else if (lev == "level_info")
                    {
                      level |= LOG_LEVEL_INFO;
                    }
                  else if (lev == "level_function")
                    {
                      level |= LOG_LEVEL_FUNCTION;
                    }
                  else if (lev == "level_logic")
                    {
                      level |= LOG_LEVEL_LOGIC;
                    }
                  else if (lev == "level_all")
                    {
                      level |= LOG_LEVEL_ALL;
                    }
                } while (next_lev != std::string::npos);

              Enable ((enum LogLevel)level);
            }
        }
      cur = next + 1;
    }
#endif
}


bool 
LogComponent::IsEnabled (enum LogLevel level) const
{
  //  LogComponentEnableEnvVar ();
  return (level & m_levels) ? 1 : 0;
}

bool
LogComponent::IsNoneEnabled (void) const
{
  return m_levels == 0;
}

void 
LogComponent::Enable (enum LogLevel level)
{
  m_levels |= level;
}

void 
LogComponent::Disable (enum LogLevel level)
{
  m_levels &= ~level;
}

char const *
LogComponent::Name (void) const
{
  return m_name;
}


void 
LogComponentEnable (char const *name, enum LogLevel level)
{
  ComponentList *components = GetComponentList ();
  for (ComponentListI i = components->begin ();
       i != components->end ();
       i++)
    {
      if (i->first.compare (name) == 0) 
	{
	  i->second->Enable (level);
	  break;
	}
    }  
}

void 
LogComponentEnableAll (enum LogLevel level)
{
  ComponentList *components = GetComponentList ();
  for (ComponentListI i = components->begin ();
       i != components->end ();
       i++)
    {
      i->second->Enable (level);
    }  
}

void 
LogComponentDisable (char const *name, enum LogLevel level)
{
  ComponentList *components = GetComponentList ();
  for (ComponentListI i = components->begin ();
       i != components->end ();
       i++)
    {
      if (i->first.compare (name) == 0) 
	{
	  i->second->Disable (level);
	  break;
	}
    }  
}

void 
LogComponentDisableAll (enum LogLevel level)
{
  ComponentList *components = GetComponentList ();
  for (ComponentListI i = components->begin ();
       i != components->end ();
       i++)
    {
      i->second->Disable (level);
    }  
}

void 
LogComponentPrintList (void)
{
  ComponentList *components = GetComponentList ();
  for (ComponentListI i = components->begin ();
       i != components->end ();
       i++)
    {
      std::cout << i->first << "=";
      if (i->second->IsNoneEnabled ())
        {
          std::cout << "0" << std::endl;
          continue;
        }
      if (i->second->IsEnabled (LOG_ERROR))
        {
          std::cout << "error";
        }
      if (i->second->IsEnabled (LOG_WARN))
        {
          std::cout << "|warn";
        }
      if (i->second->IsEnabled (LOG_DEBUG))
        {
          std::cout << "|debug";
        }
      if (i->second->IsEnabled (LOG_INFO))
        {
          std::cout << "|info";
        }
      if (i->second->IsEnabled (LOG_FUNCTION))
        {
          std::cout << "|function";
        }
      if (i->second->IsEnabled (LOG_LOGIC))
        {
          std::cout << "|logic";
        }
      if (i->second->IsEnabled (LOG_ALL))
        {
          std::cout << "|all";
        }
      std::cout << std::endl;
    }
}

void LogSetTimePrinter (LogTimePrinter printer)
{
  g_logTimePrinter = printer;
}
LogTimePrinter LogGetTimePrinter(void)
{
  return g_logTimePrinter;
}

void LogSetNodePrinter (LogNodePrinter printer)
{
  g_logNodePrinter = printer;
}
LogNodePrinter LogGetNodePrinter(void)
{
  return g_logNodePrinter;
}


ParameterLogger::ParameterLogger (std::ostream &os)
  : m_itemNumber (0),
    m_os (os)
{}

} // namespace ns3

#else // NS3_LOG_ENABLE

namespace ns3 {

void 
LogComponentEnable (char const *name, enum LogLevel level)
{

}

void 
LogComponentEnableAll (enum LogLevel level)
{

}

void 
LogComponentDisable (char const *name, enum LogLevel level)
{

}

void 
LogComponentDisableAll (enum LogLevel level)
{

}

} // namespace ns3

#endif
