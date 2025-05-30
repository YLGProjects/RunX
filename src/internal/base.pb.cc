// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: base.proto
// Protobuf C++ Version: 6.30.2

#include "base.pb.h"

#include <algorithm>
#include <type_traits>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/generated_message_tctable_impl.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace ylg {
namespace internal {

inline constexpr PluginBase::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : _cached_size_{0},
        _name_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        _version_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        _loglevel_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        _installedlocation_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        _installedtimestamp_{::uint64_t{0u}},
        _startedtimestamp_{::uint64_t{0u}},
        _runningduration_{::uint64_t{0u}} {}

template <typename>
PROTOBUF_CONSTEXPR PluginBase::PluginBase(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(PluginBase_class_data_.base()),
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(),
#endif  // PROTOBUF_CUSTOM_VTABLE
      _impl_(::_pbi::ConstantInitialized()) {
}
struct PluginBaseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PluginBaseDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~PluginBaseDefaultTypeInternal() {}
  union {
    PluginBase _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PluginBaseDefaultTypeInternal _PluginBase_default_instance_;
}  // namespace internal
}  // namespace ylg
static const ::_pb::EnumDescriptor* PROTOBUF_NONNULL
    file_level_enum_descriptors_base_2eproto[1];
static constexpr const ::_pb::ServiceDescriptor *PROTOBUF_NONNULL *PROTOBUF_NULLABLE
    file_level_service_descriptors_base_2eproto = nullptr;
const ::uint32_t
    TableStruct_base_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        PROTOBUF_FIELD_OFFSET(::ylg::internal::PluginBase, _impl_._has_bits_),
        PROTOBUF_FIELD_OFFSET(::ylg::internal::PluginBase, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::ylg::internal::PluginBase, _impl_._name_),
        PROTOBUF_FIELD_OFFSET(::ylg::internal::PluginBase, _impl_._version_),
        PROTOBUF_FIELD_OFFSET(::ylg::internal::PluginBase, _impl_._loglevel_),
        PROTOBUF_FIELD_OFFSET(::ylg::internal::PluginBase, _impl_._installedlocation_),
        PROTOBUF_FIELD_OFFSET(::ylg::internal::PluginBase, _impl_._installedtimestamp_),
        PROTOBUF_FIELD_OFFSET(::ylg::internal::PluginBase, _impl_._startedtimestamp_),
        PROTOBUF_FIELD_OFFSET(::ylg::internal::PluginBase, _impl_._runningduration_),
        0,
        1,
        2,
        3,
        4,
        5,
        6,
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, 15, -1, sizeof(::ylg::internal::PluginBase)},
};
static const ::_pb::Message* PROTOBUF_NONNULL const file_default_instances[] = {
    &::ylg::internal::_PluginBase_default_instance_._instance,
};
const char descriptor_table_protodef_base_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n\nbase.proto\022\014ylg.internal\"\256\001\n\nPluginBas"
    "e\022\r\n\005_name\030\001 \001(\t\022\020\n\010_version\030\002 \001(\t\022\021\n\t_l"
    "ogLevel\030\003 \001(\t\022\032\n\022_installedLocation\030\004 \001("
    "\t\022\033\n\023_installedTimestamp\030\005 \001(\004\022\031\n\021_start"
    "edTimestamp\030\006 \001(\004\022\030\n\020_runningDuration\030\007 "
    "\001(\004*$\n\nAgentState\022\n\n\006Offine\020\000\022\n\n\006Online\020"
    "\001b\006proto3"
};
static ::absl::once_flag descriptor_table_base_2eproto_once;
PROTOBUF_CONSTINIT const ::_pbi::DescriptorTable descriptor_table_base_2eproto = {
    false,
    false,
    249,
    descriptor_table_protodef_base_2eproto,
    "base.proto",
    &descriptor_table_base_2eproto_once,
    nullptr,
    0,
    1,
    schemas,
    file_default_instances,
    TableStruct_base_2eproto::offsets,
    file_level_enum_descriptors_base_2eproto,
    file_level_service_descriptors_base_2eproto,
};
namespace ylg {
namespace internal {
const ::google::protobuf::EnumDescriptor* PROTOBUF_NONNULL AgentState_descriptor() {
  ::google::protobuf::internal::AssignDescriptors(&descriptor_table_base_2eproto);
  return file_level_enum_descriptors_base_2eproto[0];
}
PROTOBUF_CONSTINIT const uint32_t AgentState_internal_data_[] = {
    131072u, 0u, };
// ===================================================================

class PluginBase::_Internal {
 public:
  using HasBits =
      decltype(std::declval<PluginBase>()._impl_._has_bits_);
  static constexpr ::int32_t kHasBitsOffset =
      8 * PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._has_bits_);
};

PluginBase::PluginBase(::google::protobuf::Arena* PROTOBUF_NULLABLE arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, PluginBase_class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:ylg.internal.PluginBase)
}
PROTOBUF_NDEBUG_INLINE PluginBase::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* PROTOBUF_NULLABLE arena, const Impl_& from,
    const ::ylg::internal::PluginBase& from_msg)
      : _has_bits_{from._has_bits_},
        _cached_size_{0},
        _name_(arena, from._name_),
        _version_(arena, from._version_),
        _loglevel_(arena, from._loglevel_),
        _installedlocation_(arena, from._installedlocation_) {}

PluginBase::PluginBase(
    ::google::protobuf::Arena* PROTOBUF_NULLABLE arena,
    const PluginBase& from)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, PluginBase_class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  PluginBase* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);
  ::memcpy(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, _installedtimestamp_),
           reinterpret_cast<const char *>(&from._impl_) +
               offsetof(Impl_, _installedtimestamp_),
           offsetof(Impl_, _runningduration_) -
               offsetof(Impl_, _installedtimestamp_) +
               sizeof(Impl_::_runningduration_));

  // @@protoc_insertion_point(copy_constructor:ylg.internal.PluginBase)
}
PROTOBUF_NDEBUG_INLINE PluginBase::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* PROTOBUF_NULLABLE arena)
      : _cached_size_{0},
        _name_(arena),
        _version_(arena),
        _loglevel_(arena),
        _installedlocation_(arena) {}

inline void PluginBase::SharedCtor(::_pb::Arena* PROTOBUF_NULLABLE arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  ::memset(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, _installedtimestamp_),
           0,
           offsetof(Impl_, _runningduration_) -
               offsetof(Impl_, _installedtimestamp_) +
               sizeof(Impl_::_runningduration_));
}
PluginBase::~PluginBase() {
  // @@protoc_insertion_point(destructor:ylg.internal.PluginBase)
  SharedDtor(*this);
}
inline void PluginBase::SharedDtor(MessageLite& self) {
  PluginBase& this_ = static_cast<PluginBase&>(self);
  this_._internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  ABSL_DCHECK(this_.GetArena() == nullptr);
  this_._impl_._name_.Destroy();
  this_._impl_._version_.Destroy();
  this_._impl_._loglevel_.Destroy();
  this_._impl_._installedlocation_.Destroy();
  this_._impl_.~Impl_();
}

inline void* PROTOBUF_NONNULL PluginBase::PlacementNew_(
    const void* PROTOBUF_NONNULL, void* PROTOBUF_NONNULL mem,
    ::google::protobuf::Arena* PROTOBUF_NULLABLE arena) {
  return ::new (mem) PluginBase(arena);
}
constexpr auto PluginBase::InternalNewImpl_() {
  return ::google::protobuf::internal::MessageCreator::CopyInit(sizeof(PluginBase),
                                            alignof(PluginBase));
}
constexpr auto PluginBase::InternalGenerateClassData_() {
  return ::google::protobuf::internal::ClassDataFull{
      ::google::protobuf::internal::ClassData{
          &_PluginBase_default_instance_._instance,
          &_table_.header,
          nullptr,  // OnDemandRegisterArenaDtor
          nullptr,  // IsInitialized
          &PluginBase::MergeImpl,
          ::google::protobuf::Message::GetNewImpl<PluginBase>(),
#if defined(PROTOBUF_CUSTOM_VTABLE)
          &PluginBase::SharedDtor,
          ::google::protobuf::Message::GetClearImpl<PluginBase>(), &PluginBase::ByteSizeLong,
              &PluginBase::_InternalSerialize,
#endif  // PROTOBUF_CUSTOM_VTABLE
          PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._cached_size_),
          false,
      },
      &PluginBase::kDescriptorMethods,
      &descriptor_table_base_2eproto,
      nullptr,  // tracker
  };
}

PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 const
    ::google::protobuf::internal::ClassDataFull PluginBase_class_data_ =
        PluginBase::InternalGenerateClassData_();

const ::google::protobuf::internal::ClassData* PROTOBUF_NONNULL PluginBase::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&PluginBase_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(PluginBase_class_data_.tc_table);
  return PluginBase_class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<3, 7, 0, 72, 2>
PluginBase::_table_ = {
  {
    PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._has_bits_),
    0, // no _extensions_
    7, 56,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967168,  // skipmap
    offsetof(decltype(_table_), field_entries),
    7,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    PluginBase_class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::ylg::internal::PluginBase>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    {::_pbi::TcParser::MiniParse, {}},
    // string _name = 1;
    {::_pbi::TcParser::FastUS1,
     {10, 0, 0, PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._name_)}},
    // string _version = 2;
    {::_pbi::TcParser::FastUS1,
     {18, 1, 0, PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._version_)}},
    // string _logLevel = 3;
    {::_pbi::TcParser::FastUS1,
     {26, 2, 0, PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._loglevel_)}},
    // string _installedLocation = 4;
    {::_pbi::TcParser::FastUS1,
     {34, 3, 0, PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._installedlocation_)}},
    // uint64 _installedTimestamp = 5;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint64_t, offsetof(PluginBase, _impl_._installedtimestamp_), 4>(),
     {40, 4, 0, PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._installedtimestamp_)}},
    // uint64 _startedTimestamp = 6;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint64_t, offsetof(PluginBase, _impl_._startedtimestamp_), 5>(),
     {48, 5, 0, PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._startedtimestamp_)}},
    // uint64 _runningDuration = 7;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint64_t, offsetof(PluginBase, _impl_._runningduration_), 6>(),
     {56, 6, 0, PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._runningduration_)}},
  }}, {{
    65535, 65535
  }}, {{
    // string _name = 1;
    {PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._name_), _Internal::kHasBitsOffset + 0, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // string _version = 2;
    {PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._version_), _Internal::kHasBitsOffset + 1, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // string _logLevel = 3;
    {PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._loglevel_), _Internal::kHasBitsOffset + 2, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // string _installedLocation = 4;
    {PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._installedlocation_), _Internal::kHasBitsOffset + 3, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // uint64 _installedTimestamp = 5;
    {PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._installedtimestamp_), _Internal::kHasBitsOffset + 4, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kUInt64)},
    // uint64 _startedTimestamp = 6;
    {PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._startedtimestamp_), _Internal::kHasBitsOffset + 5, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kUInt64)},
    // uint64 _runningDuration = 7;
    {PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._runningduration_), _Internal::kHasBitsOffset + 6, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kUInt64)},
  }},
  // no aux_entries
  {{
    "\27\5\10\11\22\0\0\0"
    "ylg.internal.PluginBase"
    "_name"
    "_version"
    "_logLevel"
    "_installedLocation"
  }},
};
PROTOBUF_NOINLINE void PluginBase::Clear() {
// @@protoc_insertion_point(message_clear_start:ylg.internal.PluginBase)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if ((cached_has_bits & 0x0000000fu) != 0) {
    if ((cached_has_bits & 0x00000001u) != 0) {
      _impl_._name_.ClearNonDefaultToEmpty();
    }
    if ((cached_has_bits & 0x00000002u) != 0) {
      _impl_._version_.ClearNonDefaultToEmpty();
    }
    if ((cached_has_bits & 0x00000004u) != 0) {
      _impl_._loglevel_.ClearNonDefaultToEmpty();
    }
    if ((cached_has_bits & 0x00000008u) != 0) {
      _impl_._installedlocation_.ClearNonDefaultToEmpty();
    }
  }
  if ((cached_has_bits & 0x00000070u) != 0) {
    ::memset(&_impl_._installedtimestamp_, 0, static_cast<::size_t>(
        reinterpret_cast<char*>(&_impl_._runningduration_) -
        reinterpret_cast<char*>(&_impl_._installedtimestamp_)) + sizeof(_impl_._runningduration_));
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

#if defined(PROTOBUF_CUSTOM_VTABLE)
::uint8_t* PROTOBUF_NONNULL PluginBase::_InternalSerialize(
    const ::google::protobuf::MessageLite& base, ::uint8_t* PROTOBUF_NONNULL target,
    ::google::protobuf::io::EpsCopyOutputStream* PROTOBUF_NONNULL stream) {
  const PluginBase& this_ = static_cast<const PluginBase&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
::uint8_t* PROTOBUF_NONNULL PluginBase::_InternalSerialize(
    ::uint8_t* PROTOBUF_NONNULL target,
    ::google::protobuf::io::EpsCopyOutputStream* PROTOBUF_NONNULL stream) const {
  const PluginBase& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
  // @@protoc_insertion_point(serialize_to_array_start:ylg.internal.PluginBase)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // string _name = 1;
  if ((this_._impl_._has_bits_[0] & 0x00000001u) != 0) {
    if (!this_._internal__name().empty()) {
      const std::string& _s = this_._internal__name();
      ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
          _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "ylg.internal.PluginBase._name");
      target = stream->WriteStringMaybeAliased(1, _s, target);
    }
  }

  // string _version = 2;
  if ((this_._impl_._has_bits_[0] & 0x00000002u) != 0) {
    if (!this_._internal__version().empty()) {
      const std::string& _s = this_._internal__version();
      ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
          _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "ylg.internal.PluginBase._version");
      target = stream->WriteStringMaybeAliased(2, _s, target);
    }
  }

  // string _logLevel = 3;
  if ((this_._impl_._has_bits_[0] & 0x00000004u) != 0) {
    if (!this_._internal__loglevel().empty()) {
      const std::string& _s = this_._internal__loglevel();
      ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
          _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "ylg.internal.PluginBase._logLevel");
      target = stream->WriteStringMaybeAliased(3, _s, target);
    }
  }

  // string _installedLocation = 4;
  if ((this_._impl_._has_bits_[0] & 0x00000008u) != 0) {
    if (!this_._internal__installedlocation().empty()) {
      const std::string& _s = this_._internal__installedlocation();
      ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
          _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "ylg.internal.PluginBase._installedLocation");
      target = stream->WriteStringMaybeAliased(4, _s, target);
    }
  }

  // uint64 _installedTimestamp = 5;
  if ((this_._impl_._has_bits_[0] & 0x00000010u) != 0) {
    if (this_._internal__installedtimestamp() != 0) {
      target = stream->EnsureSpace(target);
      target = ::_pbi::WireFormatLite::WriteUInt64ToArray(
          5, this_._internal__installedtimestamp(), target);
    }
  }

  // uint64 _startedTimestamp = 6;
  if ((this_._impl_._has_bits_[0] & 0x00000020u) != 0) {
    if (this_._internal__startedtimestamp() != 0) {
      target = stream->EnsureSpace(target);
      target = ::_pbi::WireFormatLite::WriteUInt64ToArray(
          6, this_._internal__startedtimestamp(), target);
    }
  }

  // uint64 _runningDuration = 7;
  if ((this_._impl_._has_bits_[0] & 0x00000040u) != 0) {
    if (this_._internal__runningduration() != 0) {
      target = stream->EnsureSpace(target);
      target = ::_pbi::WireFormatLite::WriteUInt64ToArray(
          7, this_._internal__runningduration(), target);
    }
  }

  if (ABSL_PREDICT_FALSE(this_._internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            this_._internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ylg.internal.PluginBase)
  return target;
}

#if defined(PROTOBUF_CUSTOM_VTABLE)
::size_t PluginBase::ByteSizeLong(const MessageLite& base) {
  const PluginBase& this_ = static_cast<const PluginBase&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
::size_t PluginBase::ByteSizeLong() const {
  const PluginBase& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
  // @@protoc_insertion_point(message_byte_size_start:ylg.internal.PluginBase)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void)cached_has_bits;

  ::_pbi::Prefetch5LinesFrom7Lines(&this_);
  cached_has_bits = this_._impl_._has_bits_[0];
  if ((cached_has_bits & 0x0000007fu) != 0) {
    // string _name = 1;
    if ((cached_has_bits & 0x00000001u) != 0) {
      if (!this_._internal__name().empty()) {
        total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                        this_._internal__name());
      }
    }
    // string _version = 2;
    if ((cached_has_bits & 0x00000002u) != 0) {
      if (!this_._internal__version().empty()) {
        total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                        this_._internal__version());
      }
    }
    // string _logLevel = 3;
    if ((cached_has_bits & 0x00000004u) != 0) {
      if (!this_._internal__loglevel().empty()) {
        total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                        this_._internal__loglevel());
      }
    }
    // string _installedLocation = 4;
    if ((cached_has_bits & 0x00000008u) != 0) {
      if (!this_._internal__installedlocation().empty()) {
        total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                        this_._internal__installedlocation());
      }
    }
    // uint64 _installedTimestamp = 5;
    if ((cached_has_bits & 0x00000010u) != 0) {
      if (this_._internal__installedtimestamp() != 0) {
        total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(
            this_._internal__installedtimestamp());
      }
    }
    // uint64 _startedTimestamp = 6;
    if ((cached_has_bits & 0x00000020u) != 0) {
      if (this_._internal__startedtimestamp() != 0) {
        total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(
            this_._internal__startedtimestamp());
      }
    }
    // uint64 _runningDuration = 7;
    if ((cached_has_bits & 0x00000040u) != 0) {
      if (this_._internal__runningduration() != 0) {
        total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(
            this_._internal__runningduration());
      }
    }
  }
  return this_.MaybeComputeUnknownFieldsSize(total_size,
                                             &this_._impl_._cached_size_);
}

void PluginBase::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<PluginBase*>(&to_msg);
  auto& from = static_cast<const PluginBase&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:ylg.internal.PluginBase)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._impl_._has_bits_[0];
  if ((cached_has_bits & 0x0000007fu) != 0) {
    if ((cached_has_bits & 0x00000001u) != 0) {
      if (!from._internal__name().empty()) {
        _this->_internal_set__name(from._internal__name());
      } else {
        if (_this->_impl_._name_.IsDefault()) {
          _this->_internal_set__name("");
        }
      }
    }
    if ((cached_has_bits & 0x00000002u) != 0) {
      if (!from._internal__version().empty()) {
        _this->_internal_set__version(from._internal__version());
      } else {
        if (_this->_impl_._version_.IsDefault()) {
          _this->_internal_set__version("");
        }
      }
    }
    if ((cached_has_bits & 0x00000004u) != 0) {
      if (!from._internal__loglevel().empty()) {
        _this->_internal_set__loglevel(from._internal__loglevel());
      } else {
        if (_this->_impl_._loglevel_.IsDefault()) {
          _this->_internal_set__loglevel("");
        }
      }
    }
    if ((cached_has_bits & 0x00000008u) != 0) {
      if (!from._internal__installedlocation().empty()) {
        _this->_internal_set__installedlocation(from._internal__installedlocation());
      } else {
        if (_this->_impl_._installedlocation_.IsDefault()) {
          _this->_internal_set__installedlocation("");
        }
      }
    }
    if ((cached_has_bits & 0x00000010u) != 0) {
      if (from._internal__installedtimestamp() != 0) {
        _this->_impl_._installedtimestamp_ = from._impl_._installedtimestamp_;
      }
    }
    if ((cached_has_bits & 0x00000020u) != 0) {
      if (from._internal__startedtimestamp() != 0) {
        _this->_impl_._startedtimestamp_ = from._impl_._startedtimestamp_;
      }
    }
    if ((cached_has_bits & 0x00000040u) != 0) {
      if (from._internal__runningduration() != 0) {
        _this->_impl_._runningduration_ = from._impl_._runningduration_;
      }
    }
  }
  _this->_impl_._has_bits_[0] |= cached_has_bits;
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void PluginBase::CopyFrom(const PluginBase& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ylg.internal.PluginBase)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}


void PluginBase::InternalSwap(PluginBase* PROTOBUF_RESTRICT PROTOBUF_NONNULL other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_._name_, &other->_impl_._name_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_._version_, &other->_impl_._version_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_._loglevel_, &other->_impl_._loglevel_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_._installedlocation_, &other->_impl_._installedlocation_, arena);
  ::google::protobuf::internal::memswap<
      PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._runningduration_)
      + sizeof(PluginBase::_impl_._runningduration_)
      - PROTOBUF_FIELD_OFFSET(PluginBase, _impl_._installedtimestamp_)>(
          reinterpret_cast<char*>(&_impl_._installedtimestamp_),
          reinterpret_cast<char*>(&other->_impl_._installedtimestamp_));
}

::google::protobuf::Metadata PluginBase::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace internal
}  // namespace ylg
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::std::false_type
    _static_init2_ [[maybe_unused]] =
        (::_pbi::AddDescriptors(&descriptor_table_base_2eproto),
         ::std::false_type{});
#include "google/protobuf/port_undef.inc"
