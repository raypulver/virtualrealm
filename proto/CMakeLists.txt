file(GLOB ProtoFiles RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.proto)
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${ProtoFiles})
#set(PROTOBUF_IMPORT_DIRS RELATIVE ${PROJECT_BINARY_DIR} ./proto)
add_library(virtualproto OBJECT ${ProtoSources} ${ProtoHeaders})
