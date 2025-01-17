#pragma once

#include "Arduino.h"
#include "NukiConstants.h"

namespace Nuki {

enum class EventType {
  KeyTurnerStatusUpdated
};

class SmartlockEventHandler {
  public:
    virtual ~SmartlockEventHandler() {};
    virtual void notify(EventType eventType) = 0;
};

enum CmdResult : uint8_t {
  Success   = 1,
  Failed    = 2,
  TimeOut   = 3,
  Working   = 4,
  NotPaired = 5,
  Error     = 99
};

enum class PairingState {
  InitPairing       = 0,
  ReqRemPubKey      = 1,
  RecRemPubKey      = 2,
  SendPubKey        = 3,
  GenKeyPair        = 4,
  CalculateAuth     = 5,
  SendAuth          = 6,
  SendAuthData      = 7,
  SendAuthIdConf    = 8,
  RecStatus         = 9,
  Success           = 10,
  Timeout           = 99
};

enum class CommandState {
  Idle                  = 0,
  CmdReceived           = 1,
  ChallengeSent         = 2,
  ChallengeRespReceived = 3,
  CmdSent               = 4,
  CmdAccepted           = 5,
  TimeOut               = 6
};

enum class CommandType {
  Command                       = 0,
  CommandWithChallenge          = 1,
  CommandWithChallengeAndAccept = 2,
  CommandWithChallengeAndPin    = 3
};

struct Action {
  CommandType cmdType;
  Command command;
  unsigned char payload[100] {0};
  uint8_t payloadLen = 0;
};

inline void cmdResultToString(const CmdResult state, char* str) {
  switch (state) {
    case CmdResult::Success:
      strcpy(str, "success");
      break;
    case CmdResult::Failed:
      strcpy(str, "failed");
      break;
    case CmdResult::TimeOut:
      strcpy(str, "timeOut");
      break;
    case CmdResult::Working:
      strcpy(str, "working");
      break;
    case CmdResult::NotPaired:
      strcpy(str, "notPaired");
      break;
    case CmdResult::Error:
      strcpy(str, "error");
      break;
    default:
      strcpy(str, "undefined");
      break;
  }
}
} // namespace Nuki
