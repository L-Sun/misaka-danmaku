// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: kademlia.proto

#include "kademlia.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
constexpr KademliaMessage::KademliaMessage(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : time_(nullptr)
  , messageid_(PROTOBUF_ULONGLONG(0))
  , _oneof_case_{}{}
struct KademliaMessageDefaultTypeInternal {
  constexpr KademliaMessageDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~KademliaMessageDefaultTypeInternal() {}
  union {
    KademliaMessage _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT KademliaMessageDefaultTypeInternal _KademliaMessage_default_instance_;
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_kademlia_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_kademlia_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_kademlia_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_kademlia_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::KademliaMessage, _internal_metadata_),
  ~0u,  // no _extensions_
  PROTOBUF_FIELD_OFFSET(::KademliaMessage, _oneof_case_[0]),
  ~0u,  // no _weak_field_map_
  ::PROTOBUF_NAMESPACE_ID::internal::kInvalidFieldOffsetTag,
  ::PROTOBUF_NAMESPACE_ID::internal::kInvalidFieldOffsetTag,
  PROTOBUF_FIELD_OFFSET(::KademliaMessage, messageid_),
  PROTOBUF_FIELD_OFFSET(::KademliaMessage, time_),
  PROTOBUF_FIELD_OFFSET(::KademliaMessage, payload_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::KademliaMessage)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_KademliaMessage_default_instance_),
};

const char descriptor_table_protodef_kademlia_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\016kademlia.proto\032\037google/protobuf/timest"
  "amp.proto\032\rrequest.proto\032\016response.proto"
  "\"\225\001\n\017KademliaMessage\022\033\n\007request\030\001 \001(\0132\010."
  "RequestH\000\022\035\n\010response\030\002 \001(\0132\t.ResponseH\000"
  "\022\021\n\tmessageID\030\004 \001(\004\022(\n\004time\030\005 \001(\0132\032.goog"
  "le.protobuf.TimestampB\t\n\007payloadb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_kademlia_2eproto_deps[3] = {
  &::descriptor_table_google_2fprotobuf_2ftimestamp_2eproto,
  &::descriptor_table_request_2eproto,
  &::descriptor_table_response_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_kademlia_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_kademlia_2eproto = {
  false, false, 240, descriptor_table_protodef_kademlia_2eproto, "kademlia.proto", 
  &descriptor_table_kademlia_2eproto_once, descriptor_table_kademlia_2eproto_deps, 3, 1,
  schemas, file_default_instances, TableStruct_kademlia_2eproto::offsets,
  file_level_metadata_kademlia_2eproto, file_level_enum_descriptors_kademlia_2eproto, file_level_service_descriptors_kademlia_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK ::PROTOBUF_NAMESPACE_ID::Metadata
descriptor_table_kademlia_2eproto_metadata_getter(int index) {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_kademlia_2eproto);
  return descriptor_table_kademlia_2eproto.file_level_metadata[index];
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_kademlia_2eproto(&descriptor_table_kademlia_2eproto);

// ===================================================================

class KademliaMessage::_Internal {
 public:
  static const ::Request& request(const KademliaMessage* msg);
  static const ::Response& response(const KademliaMessage* msg);
  static const PROTOBUF_NAMESPACE_ID::Timestamp& time(const KademliaMessage* msg);
};

const ::Request&
KademliaMessage::_Internal::request(const KademliaMessage* msg) {
  return *msg->payload_.request_;
}
const ::Response&
KademliaMessage::_Internal::response(const KademliaMessage* msg) {
  return *msg->payload_.response_;
}
const PROTOBUF_NAMESPACE_ID::Timestamp&
KademliaMessage::_Internal::time(const KademliaMessage* msg) {
  return *msg->time_;
}
void KademliaMessage::set_allocated_request(::Request* request) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArena();
  clear_payload();
  if (request) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(request)->GetArena();
    if (message_arena != submessage_arena) {
      request = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, request, submessage_arena);
    }
    set_has_request();
    payload_.request_ = request;
  }
  // @@protoc_insertion_point(field_set_allocated:KademliaMessage.request)
}
void KademliaMessage::clear_request() {
  if (_internal_has_request()) {
    if (GetArena() == nullptr) {
      delete payload_.request_;
    }
    clear_has_payload();
  }
}
void KademliaMessage::set_allocated_response(::Response* response) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArena();
  clear_payload();
  if (response) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(response)->GetArena();
    if (message_arena != submessage_arena) {
      response = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, response, submessage_arena);
    }
    set_has_response();
    payload_.response_ = response;
  }
  // @@protoc_insertion_point(field_set_allocated:KademliaMessage.response)
}
void KademliaMessage::clear_response() {
  if (_internal_has_response()) {
    if (GetArena() == nullptr) {
      delete payload_.response_;
    }
    clear_has_payload();
  }
}
void KademliaMessage::clear_time() {
  if (GetArena() == nullptr && time_ != nullptr) {
    delete time_;
  }
  time_ = nullptr;
}
KademliaMessage::KademliaMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:KademliaMessage)
}
KademliaMessage::KademliaMessage(const KademliaMessage& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_time()) {
    time_ = new PROTOBUF_NAMESPACE_ID::Timestamp(*from.time_);
  } else {
    time_ = nullptr;
  }
  messageid_ = from.messageid_;
  clear_has_payload();
  switch (from.payload_case()) {
    case kRequest: {
      _internal_mutable_request()->::Request::MergeFrom(from._internal_request());
      break;
    }
    case kResponse: {
      _internal_mutable_response()->::Response::MergeFrom(from._internal_response());
      break;
    }
    case PAYLOAD_NOT_SET: {
      break;
    }
  }
  // @@protoc_insertion_point(copy_constructor:KademliaMessage)
}

void KademliaMessage::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&time_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&messageid_) -
    reinterpret_cast<char*>(&time_)) + sizeof(messageid_));
clear_has_payload();
}

KademliaMessage::~KademliaMessage() {
  // @@protoc_insertion_point(destructor:KademliaMessage)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void KademliaMessage::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  if (this != internal_default_instance()) delete time_;
  if (has_payload()) {
    clear_payload();
  }
}

void KademliaMessage::ArenaDtor(void* object) {
  KademliaMessage* _this = reinterpret_cast< KademliaMessage* >(object);
  (void)_this;
}
void KademliaMessage::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void KademliaMessage::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void KademliaMessage::clear_payload() {
// @@protoc_insertion_point(one_of_clear_start:KademliaMessage)
  switch (payload_case()) {
    case kRequest: {
      if (GetArena() == nullptr) {
        delete payload_.request_;
      }
      break;
    }
    case kResponse: {
      if (GetArena() == nullptr) {
        delete payload_.response_;
      }
      break;
    }
    case PAYLOAD_NOT_SET: {
      break;
    }
  }
  _oneof_case_[0] = PAYLOAD_NOT_SET;
}


void KademliaMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:KademliaMessage)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (GetArena() == nullptr && time_ != nullptr) {
    delete time_;
  }
  time_ = nullptr;
  messageid_ = PROTOBUF_ULONGLONG(0);
  clear_payload();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* KademliaMessage::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .Request request = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_request(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .Response response = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_response(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint64 messageID = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          messageid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .google.protobuf.Timestamp time = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 42)) {
          ptr = ctx->ParseMessage(_internal_mutable_time(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* KademliaMessage::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:KademliaMessage)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .Request request = 1;
  if (_internal_has_request()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        1, _Internal::request(this), target, stream);
  }

  // .Response response = 2;
  if (_internal_has_response()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::response(this), target, stream);
  }

  // uint64 messageID = 4;
  if (this->messageid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(4, this->_internal_messageid(), target);
  }

  // .google.protobuf.Timestamp time = 5;
  if (this->has_time()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        5, _Internal::time(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:KademliaMessage)
  return target;
}

size_t KademliaMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:KademliaMessage)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .google.protobuf.Timestamp time = 5;
  if (this->has_time()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *time_);
  }

  // uint64 messageID = 4;
  if (this->messageid() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
        this->_internal_messageid());
  }

  switch (payload_case()) {
    // .Request request = 1;
    case kRequest: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *payload_.request_);
      break;
    }
    // .Response response = 2;
    case kResponse: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *payload_.response_);
      break;
    }
    case PAYLOAD_NOT_SET: {
      break;
    }
  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void KademliaMessage::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:KademliaMessage)
  GOOGLE_DCHECK_NE(&from, this);
  const KademliaMessage* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<KademliaMessage>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:KademliaMessage)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:KademliaMessage)
    MergeFrom(*source);
  }
}

void KademliaMessage::MergeFrom(const KademliaMessage& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:KademliaMessage)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_time()) {
    _internal_mutable_time()->PROTOBUF_NAMESPACE_ID::Timestamp::MergeFrom(from._internal_time());
  }
  if (from.messageid() != 0) {
    _internal_set_messageid(from._internal_messageid());
  }
  switch (from.payload_case()) {
    case kRequest: {
      _internal_mutable_request()->::Request::MergeFrom(from._internal_request());
      break;
    }
    case kResponse: {
      _internal_mutable_response()->::Response::MergeFrom(from._internal_response());
      break;
    }
    case PAYLOAD_NOT_SET: {
      break;
    }
  }
}

void KademliaMessage::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:KademliaMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void KademliaMessage::CopyFrom(const KademliaMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:KademliaMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool KademliaMessage::IsInitialized() const {
  return true;
}

void KademliaMessage::InternalSwap(KademliaMessage* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(KademliaMessage, messageid_)
      + sizeof(KademliaMessage::messageid_)
      - PROTOBUF_FIELD_OFFSET(KademliaMessage, time_)>(
          reinterpret_cast<char*>(&time_),
          reinterpret_cast<char*>(&other->time_));
  swap(payload_, other->payload_);
  swap(_oneof_case_[0], other->_oneof_case_[0]);
}

::PROTOBUF_NAMESPACE_ID::Metadata KademliaMessage::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::KademliaMessage* Arena::CreateMaybeMessage< ::KademliaMessage >(Arena* arena) {
  return Arena::CreateMessageInternal< ::KademliaMessage >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>