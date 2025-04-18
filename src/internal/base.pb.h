// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: base.proto
// Protobuf C++ Version: 4.25.1

#ifndef GOOGLE_PROTOBUF_INCLUDED_base_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_base_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION < 4025000
#error "This file was generated by a newer version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please update"
#error "your headers."
#endif  // PROTOBUF_VERSION

#if 4025001 < PROTOBUF_MIN_PROTOC_VERSION
#error "This file was generated by an older version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please"
#error "regenerate this file with a newer version of protoc."
#endif  // PROTOBUF_MIN_PROTOC_VERSION
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/generated_enum_reflection.h"
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_base_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_base_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_base_2eproto;
namespace ylg {
namespace internal {
class PluginBase;
struct PluginBaseDefaultTypeInternal;
extern PluginBaseDefaultTypeInternal _PluginBase_default_instance_;
}  // namespace internal
}  // namespace ylg
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace ylg {
namespace internal {
enum AgentState : int {
  Offine = 0,
  Online = 1,
  AgentState_INT_MIN_SENTINEL_DO_NOT_USE_ =
      std::numeric_limits<::int32_t>::min(),
  AgentState_INT_MAX_SENTINEL_DO_NOT_USE_ =
      std::numeric_limits<::int32_t>::max(),
};

bool AgentState_IsValid(int value);
extern const uint32_t AgentState_internal_data_[];
constexpr AgentState AgentState_MIN = static_cast<AgentState>(0);
constexpr AgentState AgentState_MAX = static_cast<AgentState>(1);
constexpr int AgentState_ARRAYSIZE = 1 + 1;
const ::google::protobuf::EnumDescriptor*
AgentState_descriptor();
template <typename T>
const std::string& AgentState_Name(T value) {
  static_assert(std::is_same<T, AgentState>::value ||
                    std::is_integral<T>::value,
                "Incorrect type passed to AgentState_Name().");
  return AgentState_Name(static_cast<AgentState>(value));
}
template <>
inline const std::string& AgentState_Name(AgentState value) {
  return ::google::protobuf::internal::NameOfDenseEnum<AgentState_descriptor,
                                                 0, 1>(
      static_cast<int>(value));
}
inline bool AgentState_Parse(absl::string_view name, AgentState* value) {
  return ::google::protobuf::internal::ParseNamedEnum<AgentState>(
      AgentState_descriptor(), name, value);
}

// ===================================================================


// -------------------------------------------------------------------

class PluginBase final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ylg.internal.PluginBase) */ {
 public:
  inline PluginBase() : PluginBase(nullptr) {}
  ~PluginBase() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR PluginBase(::google::protobuf::internal::ConstantInitialized);

  inline PluginBase(const PluginBase& from)
      : PluginBase(nullptr, from) {}
  PluginBase(PluginBase&& from) noexcept
    : PluginBase() {
    *this = ::std::move(from);
  }

  inline PluginBase& operator=(const PluginBase& from) {
    CopyFrom(from);
    return *this;
  }
  inline PluginBase& operator=(PluginBase&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const PluginBase& default_instance() {
    return *internal_default_instance();
  }
  static inline const PluginBase* internal_default_instance() {
    return reinterpret_cast<const PluginBase*>(
               &_PluginBase_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(PluginBase& a, PluginBase& b) {
    a.Swap(&b);
  }
  inline void Swap(PluginBase* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr &&
        GetArena() == other->GetArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PluginBase* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  PluginBase* New(::google::protobuf::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<PluginBase>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const PluginBase& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom( const PluginBase& from) {
    PluginBase::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  ::google::protobuf::internal::CachedSize* AccessCachedSize() const final;
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(PluginBase* other);

  private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "ylg.internal.PluginBase";
  }
  protected:
  explicit PluginBase(::google::protobuf::Arena* arena);
  PluginBase(::google::protobuf::Arena* arena, const PluginBase& from);
  public:

  static const ClassData _class_data_;
  const ::google::protobuf::Message::ClassData*GetClassData() const final;

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNameFieldNumber = 1,
    kVersionFieldNumber = 2,
    kLogLevelFieldNumber = 3,
    kInstalledLocationFieldNumber = 4,
    kInstalledTimestampFieldNumber = 5,
    kStartedTimestampFieldNumber = 6,
    kRunningDurationFieldNumber = 7,
  };
  // string _name = 1;
  void clear__name() ;
  const std::string& _name() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set__name(Arg_&& arg, Args_... args);
  std::string* mutable__name();
  PROTOBUF_NODISCARD std::string* release__name();
  void set_allocated__name(std::string* value);

  private:
  const std::string& _internal__name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set__name(
      const std::string& value);
  std::string* _internal_mutable__name();

  public:
  // string _version = 2;
  void clear__version() ;
  const std::string& _version() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set__version(Arg_&& arg, Args_... args);
  std::string* mutable__version();
  PROTOBUF_NODISCARD std::string* release__version();
  void set_allocated__version(std::string* value);

  private:
  const std::string& _internal__version() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set__version(
      const std::string& value);
  std::string* _internal_mutable__version();

  public:
  // string _logLevel = 3;
  void clear__loglevel() ;
  const std::string& _loglevel() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set__loglevel(Arg_&& arg, Args_... args);
  std::string* mutable__loglevel();
  PROTOBUF_NODISCARD std::string* release__loglevel();
  void set_allocated__loglevel(std::string* value);

  private:
  const std::string& _internal__loglevel() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set__loglevel(
      const std::string& value);
  std::string* _internal_mutable__loglevel();

  public:
  // string _installedLocation = 4;
  void clear__installedlocation() ;
  const std::string& _installedlocation() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set__installedlocation(Arg_&& arg, Args_... args);
  std::string* mutable__installedlocation();
  PROTOBUF_NODISCARD std::string* release__installedlocation();
  void set_allocated__installedlocation(std::string* value);

  private:
  const std::string& _internal__installedlocation() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set__installedlocation(
      const std::string& value);
  std::string* _internal_mutable__installedlocation();

  public:
  // uint64 _installedTimestamp = 5;
  void clear__installedtimestamp() ;
  ::uint64_t _installedtimestamp() const;
  void set__installedtimestamp(::uint64_t value);

  private:
  ::uint64_t _internal__installedtimestamp() const;
  void _internal_set__installedtimestamp(::uint64_t value);

  public:
  // uint64 _startedTimestamp = 6;
  void clear__startedtimestamp() ;
  ::uint64_t _startedtimestamp() const;
  void set__startedtimestamp(::uint64_t value);

  private:
  ::uint64_t _internal__startedtimestamp() const;
  void _internal_set__startedtimestamp(::uint64_t value);

  public:
  // uint64 _runningDuration = 7;
  void clear__runningduration() ;
  ::uint64_t _runningduration() const;
  void set__runningduration(::uint64_t value);

  private:
  ::uint64_t _internal__runningduration() const;
  void _internal_set__runningduration(::uint64_t value);

  public:
  // @@protoc_insertion_point(class_scope:ylg.internal.PluginBase)
 private:
  class _Internal;

  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      3, 7, 0,
      72, 2>
      _table_;
  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {

        inline explicit constexpr Impl_(
            ::google::protobuf::internal::ConstantInitialized) noexcept;
        inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                              ::google::protobuf::Arena* arena);
        inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                              ::google::protobuf::Arena* arena, const Impl_& from);
    ::google::protobuf::internal::ArenaStringPtr _name_;
    ::google::protobuf::internal::ArenaStringPtr _version_;
    ::google::protobuf::internal::ArenaStringPtr _loglevel_;
    ::google::protobuf::internal::ArenaStringPtr _installedlocation_;
    ::uint64_t _installedtimestamp_;
    ::uint64_t _startedtimestamp_;
    ::uint64_t _runningduration_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_base_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// PluginBase

// string _name = 1;
inline void PluginBase::clear__name() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._name_.ClearToEmpty();
}
inline const std::string& PluginBase::_name() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:ylg.internal.PluginBase._name)
  return _internal__name();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void PluginBase::set__name(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_._name_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:ylg.internal.PluginBase._name)
}
inline std::string* PluginBase::mutable__name() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable__name();
  // @@protoc_insertion_point(field_mutable:ylg.internal.PluginBase._name)
  return _s;
}
inline const std::string& PluginBase::_internal__name() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_._name_.Get();
}
inline void PluginBase::_internal_set__name(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_._name_.Set(value, GetArena());
}
inline std::string* PluginBase::_internal_mutable__name() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  return _impl_._name_.Mutable( GetArena());
}
inline std::string* PluginBase::release__name() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:ylg.internal.PluginBase._name)
  return _impl_._name_.Release();
}
inline void PluginBase::set_allocated__name(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._name_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_._name_.IsDefault()) {
          _impl_._name_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:ylg.internal.PluginBase._name)
}

// string _version = 2;
inline void PluginBase::clear__version() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._version_.ClearToEmpty();
}
inline const std::string& PluginBase::_version() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:ylg.internal.PluginBase._version)
  return _internal__version();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void PluginBase::set__version(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_._version_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:ylg.internal.PluginBase._version)
}
inline std::string* PluginBase::mutable__version() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable__version();
  // @@protoc_insertion_point(field_mutable:ylg.internal.PluginBase._version)
  return _s;
}
inline const std::string& PluginBase::_internal__version() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_._version_.Get();
}
inline void PluginBase::_internal_set__version(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_._version_.Set(value, GetArena());
}
inline std::string* PluginBase::_internal_mutable__version() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  return _impl_._version_.Mutable( GetArena());
}
inline std::string* PluginBase::release__version() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:ylg.internal.PluginBase._version)
  return _impl_._version_.Release();
}
inline void PluginBase::set_allocated__version(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._version_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_._version_.IsDefault()) {
          _impl_._version_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:ylg.internal.PluginBase._version)
}

// string _logLevel = 3;
inline void PluginBase::clear__loglevel() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._loglevel_.ClearToEmpty();
}
inline const std::string& PluginBase::_loglevel() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:ylg.internal.PluginBase._logLevel)
  return _internal__loglevel();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void PluginBase::set__loglevel(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_._loglevel_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:ylg.internal.PluginBase._logLevel)
}
inline std::string* PluginBase::mutable__loglevel() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable__loglevel();
  // @@protoc_insertion_point(field_mutable:ylg.internal.PluginBase._logLevel)
  return _s;
}
inline const std::string& PluginBase::_internal__loglevel() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_._loglevel_.Get();
}
inline void PluginBase::_internal_set__loglevel(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_._loglevel_.Set(value, GetArena());
}
inline std::string* PluginBase::_internal_mutable__loglevel() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  return _impl_._loglevel_.Mutable( GetArena());
}
inline std::string* PluginBase::release__loglevel() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:ylg.internal.PluginBase._logLevel)
  return _impl_._loglevel_.Release();
}
inline void PluginBase::set_allocated__loglevel(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._loglevel_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_._loglevel_.IsDefault()) {
          _impl_._loglevel_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:ylg.internal.PluginBase._logLevel)
}

// string _installedLocation = 4;
inline void PluginBase::clear__installedlocation() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._installedlocation_.ClearToEmpty();
}
inline const std::string& PluginBase::_installedlocation() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:ylg.internal.PluginBase._installedLocation)
  return _internal__installedlocation();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void PluginBase::set__installedlocation(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_._installedlocation_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:ylg.internal.PluginBase._installedLocation)
}
inline std::string* PluginBase::mutable__installedlocation() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable__installedlocation();
  // @@protoc_insertion_point(field_mutable:ylg.internal.PluginBase._installedLocation)
  return _s;
}
inline const std::string& PluginBase::_internal__installedlocation() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_._installedlocation_.Get();
}
inline void PluginBase::_internal_set__installedlocation(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_._installedlocation_.Set(value, GetArena());
}
inline std::string* PluginBase::_internal_mutable__installedlocation() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  return _impl_._installedlocation_.Mutable( GetArena());
}
inline std::string* PluginBase::release__installedlocation() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:ylg.internal.PluginBase._installedLocation)
  return _impl_._installedlocation_.Release();
}
inline void PluginBase::set_allocated__installedlocation(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._installedlocation_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_._installedlocation_.IsDefault()) {
          _impl_._installedlocation_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:ylg.internal.PluginBase._installedLocation)
}

// uint64 _installedTimestamp = 5;
inline void PluginBase::clear__installedtimestamp() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._installedtimestamp_ = ::uint64_t{0u};
}
inline ::uint64_t PluginBase::_installedtimestamp() const {
  // @@protoc_insertion_point(field_get:ylg.internal.PluginBase._installedTimestamp)
  return _internal__installedtimestamp();
}
inline void PluginBase::set__installedtimestamp(::uint64_t value) {
  _internal_set__installedtimestamp(value);
  // @@protoc_insertion_point(field_set:ylg.internal.PluginBase._installedTimestamp)
}
inline ::uint64_t PluginBase::_internal__installedtimestamp() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_._installedtimestamp_;
}
inline void PluginBase::_internal_set__installedtimestamp(::uint64_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_._installedtimestamp_ = value;
}

// uint64 _startedTimestamp = 6;
inline void PluginBase::clear__startedtimestamp() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._startedtimestamp_ = ::uint64_t{0u};
}
inline ::uint64_t PluginBase::_startedtimestamp() const {
  // @@protoc_insertion_point(field_get:ylg.internal.PluginBase._startedTimestamp)
  return _internal__startedtimestamp();
}
inline void PluginBase::set__startedtimestamp(::uint64_t value) {
  _internal_set__startedtimestamp(value);
  // @@protoc_insertion_point(field_set:ylg.internal.PluginBase._startedTimestamp)
}
inline ::uint64_t PluginBase::_internal__startedtimestamp() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_._startedtimestamp_;
}
inline void PluginBase::_internal_set__startedtimestamp(::uint64_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_._startedtimestamp_ = value;
}

// uint64 _runningDuration = 7;
inline void PluginBase::clear__runningduration() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._runningduration_ = ::uint64_t{0u};
}
inline ::uint64_t PluginBase::_runningduration() const {
  // @@protoc_insertion_point(field_get:ylg.internal.PluginBase._runningDuration)
  return _internal__runningduration();
}
inline void PluginBase::set__runningduration(::uint64_t value) {
  _internal_set__runningduration(value);
  // @@protoc_insertion_point(field_set:ylg.internal.PluginBase._runningDuration)
}
inline ::uint64_t PluginBase::_internal__runningduration() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_._runningduration_;
}
inline void PluginBase::_internal_set__runningduration(::uint64_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_._runningduration_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace internal
}  // namespace ylg


namespace google {
namespace protobuf {

template <>
struct is_proto_enum<::ylg::internal::AgentState> : std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor<::ylg::internal::AgentState>() {
  return ::ylg::internal::AgentState_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_base_2eproto_2epb_2eh
