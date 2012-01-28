{
  'targets': [
    {
      'target_name': 'serializer',
      'sources': [ 'php_var_unserialize.cc', 'serializer.cc' ],
      'conditions': [
      ['OS == "win"', {
      'libraries': ['-lnode.lib']
      }]]
    }
  ]
}