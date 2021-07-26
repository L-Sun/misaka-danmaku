// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: kademlia.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_kademlia_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_kademlia_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3015000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3015008 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/timestamp.pb.h>
#include "request.pb.h"
#include "response.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_kademlia_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_kademlia_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_kademlia_2eproto;
::PROTOBUF_NAMESPACE_ID::Metadata descriptor_table_kademlia_2eproto_metadata_getter(int index);
class KademliaMessage;
struct KademliaMessageDefaultTypeInternal;
extern KademliaMessageDefaultTypeInternal _KademliaMessage_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::KademliaMessage* Arena::CreateMaybeMessage<::KademliaMessage>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class KademliaMessage PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:KademliaMessage) */ {
 public:
  inline KademliaMessage() : KademliaMessage(nullptr) {}
  virtual ~KademliaMessage();
  explicit constexpr KademliaMessage(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  KademliaMessage(const KademliaMessage& from);
  KademliaMessage(KademliaMessage&& from) noexcept
    : KademliaMessage() {
    *this = ::std::move(from);
  }

  inline KademliaMessage& operator=(const KademliaMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline KademliaMessage& operator=(KademliaMessage&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const KademliaMessage& default_instance() {
    return *internal_default_instance();
  }
  enum PayloadCase {
    kRequest = 1,
    kResponse = 2,
    PAYLOAD_NOT_SET = 0,
  };

  static inline const KademliaMessage* internal_default_instance() {
    return reinterpret_cast<const KademliaMessage*>(
               &_KademliaMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(KademliaMessage& a, KademliaMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(KademliaMessage* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(KademliaMessage* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline KademliaMessage* New() const final {
    return CreateMaybeMessage<KademliaMessage>(nullptr);
  }

  KademliaMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<KademliaMessage>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const KademliaMessage& from);
  void MergeFrom(const KademliaMessage& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(KademliaMessage* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "KademliaMessage";
  }
  protected:
  explicit KademliaMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    return ::descriptor_table_kademlia_2eproto_metadata_getter(kIndexInFileMessages);
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kTimeFieldNumber = 5,
    kMessageIDFieldNumber = 4,
    kRequestFieldNumber = 1,
    kResponseFieldNumber = 2,
  };
  // .google.protobuf.Timestamp time = 5;
  bool has_time() const;
  private:
  bool _internal_has_time() const;
  public:
  void clear_time();
  const PROTOBUF_NAMESPACE_ID::Timestamp& time() const;
  PROTOBUF_NAMESPACE_ID::Timestamp* release_time();
  PROTOBUF_NAMESPACE_ID::Timestamp* mutable_time();
  void set_allocated_time(PROTOBUF_NAMESPACE_ID::Timestamp* time);
  private:
  const PROTOBUF_NAMESPACE_ID::Timestamp& _internal_time() const;
  PROTOBUF_NAMESPACE_ID::Timestamp* _internal_mutable_time();
  public:
  void unsafe_arena_set_allocated_time(
      PROTOBUF_NAMESPACE_ID::Timestamp* time);
  PROTOBUF_NAMESPACE_ID::Timestamp* unsafe_arena_release_time();

  // uint64 messageID = 4;
  void clear_messageid();
  ::PROTOBUF_NAMESPACE_ID::uint64 messageid() const;
  void set_messageid(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_messageid() const;
  void _internal_set_messageid(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // .Request request = 1;
  bool has_request() const;
  private:
  bool _internal_has_request() const;
  public:
  void clear_request();
  const ::Request& request() const;
  ::Request* release_request();
  ::Request* mutable_request();
  void set_allocated_request(::Request* request);
  private:
  const ::Request& _internal_request() const;
  ::Request* _internal_mutable_request();
  public:
  void unsafe_arena_set_allocated_request(
      ::Request* request);
  ::Request* unsafe_arena_release_request();

  // .Response response = 2;
  bool has_response() const;
  private:
  bool _internal_has_response() const;
  public:
  void clear_response();
  const ::Response& response() const;
  ::Response* release_response();
  ::Response* mutable_response();
  void set_allocated_response(::Response* response);
  private:
  const ::Response& _internal_response() const;
  ::Response* _internal_mutable_response();
  public:
  void unsafe_arena_set_allocated_response(
      ::Response* response);
  ::Response* unsafe_arena_release_response();

  void clear_payload();
  PayloadCase payload_case() const;
  // @@protoc_insertion_point(class_scope:KademliaMessage)
 private:
  class _Internal;
  void set_has_request();
  void set_has_response();

  inline bool has_payload() const;
  inline void clear_has_payload();

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  PROTOBUF_NAMESPACE_ID::Timestamp* time_;
  ::PROTOBUF_NAMESPACE_ID::uint64 messageid_;
  union PayloadUnion {
    constexpr PayloadUnion() : _constinit_{} {}
      ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized _constinit_;
    ::Request* request_;
    ::Response* response_;
  } payload_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::uint32 _oneof_case_[1];

  friend struct ::TableStruct_kademlia_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// KademliaMessage

// .Request request = 1;
inline bool KademliaMessage::_internal_has_request() const {
  return payload_case() == kRequest;
}
inline bool KademliaMessage::has_request() const {
  return _internal_has_request();
}
inline void KademliaMessage::set_has_request() {
  _oneof_case_[0] = kRequest;
}
inline ::Request* KademliaMessage::release_request() {
  // @@protoc_insertion_point(field_release:KademliaMessage.request)
  if (_internal_has_request()) {
    clear_has_payload();
      ::Request* temp = payload_.request_;
    if (GetArena() != nullptr) {
      temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
    }
    payload_.request_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::Request& KademliaMessage::_internal_request() const {
  return _internal_has_request()
      ? *payload_.request_
      : reinterpret_cast< ::Request&>(::_Request_default_instance_);
}
inline const ::Request& KademliaMessage::request() const {
  // @@protoc_insertion_point(field_get:KademliaMessage.request)
  return _internal_request();
}
inline ::Request* KademliaMessage::unsafe_arena_release_request() {
  // @@protoc_insertion_point(field_unsafe_arena_release:KademliaMessage.request)
  if (_internal_has_request()) {
    clear_has_payload();
    ::Request* temp = payload_.request_;
    payload_.request_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline void KademliaMessage::unsafe_arena_set_allocated_request(::Request* request) {
  clear_payload();
  if (request) {
    set_has_request();
    payload_.request_ = request;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:KademliaMessage.request)
}
inline ::Request* KademliaMessage::_internal_mutable_request() {
  if (!_internal_has_request()) {
    clear_payload();
    set_has_request();
    payload_.request_ = CreateMaybeMessage< ::Request >(GetArena());
  }
  return payload_.request_;
}
inline ::Request* KademliaMessage::mutable_request() {
  // @@protoc_insertion_point(field_mutable:KademliaMessage.request)
  return _internal_mutable_request();
}

// .Response response = 2;
inline bool KademliaMessage::_internal_has_response() const {
  return payload_case() == kResponse;
}
inline bool KademliaMessage::has_response() const {
  return _internal_has_response();
}
inline void KademliaMessage::set_has_response() {
  _oneof_case_[0] = kResponse;
}
inline ::Response* KademliaMessage::release_response() {
  // @@protoc_insertion_point(field_release:KademliaMessage.response)
  if (_internal_has_response()) {
    clear_has_payload();
      ::Response* temp = payload_.response_;
    if (GetArena() != nullptr) {
      temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
    }
    payload_.response_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::Response& KademliaMessage::_internal_response() const {
  return _internal_has_response()
      ? *payload_.response_
      : reinterpret_cast< ::Response&>(::_Response_default_instance_);
}
inline const ::Response& KademliaMessage::response() const {
  // @@protoc_insertion_point(field_get:KademliaMessage.response)
  return _internal_response();
}
inline ::Response* KademliaMessage::unsafe_arena_release_response() {
  // @@protoc_insertion_point(field_unsafe_arena_release:KademliaMessage.response)
  if (_internal_has_response()) {
    clear_has_payload();
    ::Response* temp = payload_.response_;
    payload_.response_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline void KademliaMessage::unsafe_arena_set_allocated_response(::Response* response) {
  clear_payload();
  if (response) {
    set_has_response();
    payload_.response_ = response;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:KademliaMessage.response)
}
inline ::Response* KademliaMessage::_internal_mutable_response() {
  if (!_internal_has_response()) {
    clear_payload();
    set_has_response();
    payload_.response_ = CreateMaybeMessage< ::Response >(GetArena());
  }
  return payload_.response_;
}
inline ::Response* KademliaMessage::mutable_response() {
  // @@protoc_insertion_point(field_mutable:KademliaMessage.response)
  return _internal_mutable_response();
}

// uint64 messageID = 4;
inline void KademliaMessage::clear_messageid() {
  messageid_ = PROTOBUF_ULONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 KademliaMessage::_internal_messageid() const {
  return messageid_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 KademliaMessage::messageid() const {
  // @@protoc_insertion_point(field_get:KademliaMessage.messageID)
  return _internal_messageid();
}
inline void KademliaMessage::_internal_set_messageid(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  messageid_ = value;
}
inline void KademliaMessage::set_messageid(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_messageid(value);
  // @@protoc_insertion_point(field_set:KademliaMessage.messageID)
}

// .google.protobuf.Timestamp time = 5;
inline bool KademliaMessage::_internal_has_time() const {
  return this != internal_default_instance() && time_ != nullptr;
}
inline bool KademliaMessage::has_time() const {
  return _internal_has_time();
}
inline const PROTOBUF_NAMESPACE_ID::Timestamp& KademliaMessage::_internal_time() const {
  const PROTOBUF_NAMESPACE_ID::Timestamp* p = time_;
  return p != nullptr ? *p : reinterpret_cast<const PROTOBUF_NAMESPACE_ID::Timestamp&>(
      PROTOBUF_NAMESPACE_ID::_Timestamp_default_instance_);
}
inline const PROTOBUF_NAMESPACE_ID::Timestamp& KademliaMessage::time() const {
  // @@protoc_insertion_point(field_get:KademliaMessage.time)
  return _internal_time();
}
inline void KademliaMessage::unsafe_arena_set_allocated_time(
    PROTOBUF_NAMESPACE_ID::Timestamp* time) {
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(time_);
  }
  time_ = time;
  if (time) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:KademliaMessage.time)
}
inline PROTOBUF_NAMESPACE_ID::Timestamp* KademliaMessage::release_time() {
  
  PROTOBUF_NAMESPACE_ID::Timestamp* temp = time_;
  time_ = nullptr;
  if (GetArena() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
  return temp;
}
inline PROTOBUF_NAMESPACE_ID::Timestamp* KademliaMessage::unsafe_arena_release_time() {
  // @@protoc_insertion_point(field_release:KademliaMessage.time)
  
  PROTOBUF_NAMESPACE_ID::Timestamp* temp = time_;
  time_ = nullptr;
  return temp;
}
inline PROTOBUF_NAMESPACE_ID::Timestamp* KademliaMessage::_internal_mutable_time() {
  
  if (time_ == nullptr) {
    auto* p = CreateMaybeMessage<PROTOBUF_NAMESPACE_ID::Timestamp>(GetArena());
    time_ = p;
  }
  return time_;
}
inline PROTOBUF_NAMESPACE_ID::Timestamp* KademliaMessage::mutable_time() {
  // @@protoc_insertion_point(field_mutable:KademliaMessage.time)
  return _internal_mutable_time();
}
inline void KademliaMessage::set_allocated_time(PROTOBUF_NAMESPACE_ID::Timestamp* time) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArena();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(time_);
  }
  if (time) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(time)->GetArena();
    if (message_arena != submessage_arena) {
      time = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, time, submessage_arena);
    }
    
  } else {
    
  }
  time_ = time;
  // @@protoc_insertion_point(field_set_allocated:KademliaMessage.time)
}

inline bool KademliaMessage::has_payload() const {
  return payload_case() != PAYLOAD_NOT_SET;
}
inline void KademliaMessage::clear_has_payload() {
  _oneof_case_[0] = PAYLOAD_NOT_SET;
}
inline KademliaMessage::PayloadCase KademliaMessage::payload_case() const {
  return KademliaMessage::PayloadCase(_oneof_case_[0]);
}
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_kademlia_2eproto
