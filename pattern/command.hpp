#pragma once

namespace pattern {
class ICommand {
 public:
  virtual void Execute() = 0;
};

class ISwitchable {
 public:
  virtual void PowerOn() = 0;
  virtual void PowerOff() = 0;
};

class Light : public ISwitchable {
 public:
  virtual void PowerOn() override { cout << "The light is on" << endl; }
  virtual void PowerOff() override { cout << "The light is off" << endl; }
};

class CloseSwitchCommand : public ICommand {
 public:
  CloseSwitchCommand(shared_ptr<ISwitchable> switchable)
      : _switchable(switchable) {}
  void Execute() { _switchable->PowerOff(); }

 private:
  shared_ptr<ISwitchable> _switchable;
};

class OpenSwitchCommand : public ICommand {
 public:
  OpenSwitchCommand(shared_ptr<ISwitchable> switchable)
      : _switchable(switchable) {}
  void Execute() { _switchable->PowerOn(); }

 private:
  shared_ptr<ISwitchable> _switchable;
};

class Switch {
 public:
  Switch(shared_ptr<ICommand> closedCommand, shared_ptr<ICommand> openedCommand)
      : _closedCommand(closedCommand), _openedCommand(openedCommand) {}
  void Close() { _closedCommand->Execute(); }
  void Open() { _openedCommand->Execute(); }

 private:
  shared_ptr<ICommand> _closedCommand;
  shared_ptr<ICommand> _openedCommand;
};

void Test(string args) {
  shared_ptr<ISwitchable> lamp = make_shared<Light>();
  shared_ptr<ICommand> switchClose = make_shared<CloseSwitchCommand>(lamp);
  shared_ptr<ICommand> switchOpen = make_shared<OpenSwitchCommand>(lamp);

  shared_ptr<Switch> toggle = make_shared<Switch>(switchClose, switchOpen);

  if (args == "ON") {
    toggle->Open();
  } else if (args == "OFF") {
    toggle->Close();
  } else {
    throw std::invalid_argument("parameter error!");
  }
}

}  // namespace pattern
