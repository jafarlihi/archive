const std = @import("std");

const BsonKind = enum(u8) {
    Unknown = 0x00,
    Double = 0x01,
    StringUTF8 = 0x02,
    Document = 0x03,
    Array = 0x04,
    Binary = 0x05,
    Undefined = 0x06,
    Oid = 0x07,
    Bool = 0x08,
    TimeUTC = 0x09,
    Null = 0x0A,
    Regexp = 0x0B,
    DBPointer = 0x0C,
    JSCode = 0x0D,
    Deprecated = 0x0E,
    JSCodeWithScope = 0x0F,
    Int32 = 0x10,
    Timestamp = 0x11,
    Int64 = 0x12,
    MaximumKey = 0x7F,
    MinimumKey = 0xFF,
};

const BsonSubtype = enum(u8) {
    Generic = 0x00,
    Function = 0x01,
    BinaryOld = 0x02,
    UuidOld = 0x03,
    Uuid = 0x04,
    Md5 = 0x05,
    UserDefined = 0x80,
};

const BsonTimestamp = struct {
    increment: i32,
    timestamp: i32,
};

const Bson = union(BsonKind) {
    Unknown,
    Double: f64,
    StringUTF8: []u8,
    Document: std.StringHashMap(Bson),
    Array: std.ArrayList(Bson),
    Binary: union(BsonSubtype) {
        Generic: []u8,
        Function: []u8,
        BinaryOld: []u8,
        UuidOld: []u8,
        Uuid: []u8,
        Md5: []u8,
        UserDefined: []u8,
    },
    Undefined,
    Oid: []u8,
    Bool: bool,
    TimeUTC: i64,
    Null,
    Regexp: struct { regex: []u8, options: []u8 },
    DBPointer: struct { refCol: []u8, refOid: []u8 },
    JSCode: []u8,
    Deprecated: []u8,
    JSCodeWithScope: []u8,
    Int32: i32,
    Timestamp: BsonTimestamp,
    Int64: i64,
    MaximumKey,
    MinimumKey,
};

pub fn newBsonDocument() !Bson {
    return Bson{ .Document = std.StringHashMap(Bson).init(std.heap.page_allocator) };
}

pub fn minkey() !Bson {
    return Bson{ .MinimumKey = {} };
}

pub fn maxkey() !Bson {
    return Bson{ .MaximumKey = {} };
}

pub fn @"null"() !Bson {
    return Bson{ .Null = {} };
}

pub fn toBson(x: f64) !Bson {
    return Bson{.Double = x};
}

pub fn toBson(obj: anytype) !void {
    var result = try newBsonDocument();
    inline for (std.meta.fields(@TypeOf(obj))) |f| {
        try result.Document.put(f.name, try toBson(@as(f.field_type, @field(obj, f.name))));
        //std.debug.print("{any}\n", .{f.field_type});
        //std.debug.print("{any}\n", .{@as(f.field_type, @field(obj, f.name))});
    }
}

pub fn main() anyerror!void {
    std.log.info("All your codebase are belong to us.", .{});
}

test "bson test" {
    const bdoc = toBson(.{
        //.minkey = try minkey(),
        //.maxkey = try maxkey(),
        .balance = 1000.23,
        //.name = "John",
        //.someTrue = true,
        //.surname = "Smith",
        //.someNull = @"null"(),
    });

    _ = try bdoc;

    try std.testing.expectEqual(10, 3 + 7);
}
