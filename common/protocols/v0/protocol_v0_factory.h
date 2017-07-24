#ifndef DWIZ_COMMON_PROTOCOLS_V0_PROTOCOL_V0_FACTORY_H
#define DWIZ_COMMON_PROTOCOLS_V0_PROTOCOL_V0_FACTORY_H

#include <common/dwiz_std.h>
#include <common/protocols/protocol_factory_interface.h>

namespace dwiz
{
class ProtocolV0Factory : public ProtocolFactoryInterface
{
public:
    virtual std::unique_ptr<LoginProtocolInterface> createLoginProtocol() override;
}; // class ProtocolV0Factory
} // namespace dwiz

#endif
