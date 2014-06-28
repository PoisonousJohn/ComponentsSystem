#include "ComponentSystem.h"

void poison::ComponentSystem::setEnabled(bool enabled) {
    if (this->enabled == enabled)
        return;

    this->enabled = enabled;
    enabledStateChanged(enabled);
}

