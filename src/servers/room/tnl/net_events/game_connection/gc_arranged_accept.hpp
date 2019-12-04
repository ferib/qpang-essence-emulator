#ifndef GC_ARRANGED_ACCEPT_HPP
#define GC_ARRANGED_ACCEPT_HPP

#include "game_net_event.hpp"

class GCArrangedAccept : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	GCArrangedAccept() : GameNetEvent{ GC_ARRANGED_ACCEPT, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};
	GCArrangedAccept(U32 senderId, U32 targetId) : GameNetEvent{ GC_ARRANGED_ACCEPT, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny }
	{
		this->senderId = senderId;
		this->targetId = targetId;
	};
	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(senderId); // ?
		bstream->write(targetId); // target uid
		bstream->write(1);
		bstream->write(1); // possible addresses count.
		bstream->write(U32(222));
		bstream->write(U16(222));

		std::string s = "123456781234567892345672345672345672345672345678";
		buffer = new ByteBuffer((U8*)s.data(), s.size());
		bstream->write(buffer);
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) 
	{
		buffer->clear();
		buffer->destroySelf();

		NET_POST_EVENT(ps);
	};

	ByteBuffer* buffer;
	U32 senderId;
	U32 targetId;

	TNL_DECLARE_CLASS(GCArrangedAccept);
};


#endif // !GC_ARRANGED_ACCEPT_HPP
