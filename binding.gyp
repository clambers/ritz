{
  "targets": [
    {
      "target_name": "ritz",
      "cflags": [ "-std=c++14" ],
      "conditions": [
        ["OS!='win'", {
          "cflags+": [ "-std=c++14" ],
          "cflags_c+": [ "-std=c++14" ],
          "cflags_cc+": [ "-std=c++14" ]
        }],
        ["OS=='mac'", {
          "xcode_settings": {
            "OTHER_CPLUSPLUSFLAGS": [ "-std=c++14" ],
            "MACOSX_DEPLOYMENT_TARGET": "10.7"
          }
        }]
      ],
      "sources": [
        "src/netstream.cc",
        "src/ritz.cc"
      ]
    }
  ]
}
