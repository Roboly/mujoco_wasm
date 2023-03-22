#include <chrono>
#include <cstdio>
#include <cstring>
#include <string>
#include <thread>
#include <vector>

#include "mujoco/mujoco.h"

#include <emscripten/fetch.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <vector>

using namespace emscripten;

int finish(const char *msg = NULL, mjModel *m = NULL) {
  if (m  ) { mj_deleteModel(m); }
  if (msg) { std::printf("%s\n", msg); }
  return 0;
}

class Model {
public:
  Model() { m = NULL; }
  Model(const std::string filename) {
    char error[1000] = "Could not load xml model";
    m = mj_loadXML(filename.c_str(), 0, error, 1000); 
    if (!m) { finish(error, m); }
  }

  static Model load_from_xml(const std::string filename) { return Model(filename); }

  mjModel *ptr       () { return m; }
  mjModel getVal     () { return *m; }
  mjOption getOptions() { return (*m).opt; }

  // MJMODEL_DEFINITIONS
  int  nq            () { return m->nq            ; }
  int  nv            () { return m->nv            ; }
  int  nu            () { return m->nu            ; }
  int  na            () { return m->na            ; }
  int  nbody         () { return m->nbody         ; }
  int  njnt          () { return m->njnt          ; }
  int  ngeom         () { return m->ngeom         ; }
  int  nsite         () { return m->nsite         ; }
  int  ncam          () { return m->ncam          ; }
  int  nlight        () { return m->nlight        ; }
  int  nmesh         () { return m->nmesh         ; }
  int  nmeshvert     () { return m->nmeshvert     ; }
  int  nmeshtexvert  () { return m->nmeshtexvert  ; }
  int  nmeshface     () { return m->nmeshface     ; }
  int  nmeshgraph    () { return m->nmeshgraph    ; }
  int  nskin         () { return m->nskin         ; }
  int  nskinvert     () { return m->nskinvert     ; }
  int  nskintexvert  () { return m->nskintexvert  ; }
  int  nskinface     () { return m->nskinface     ; }
  int  nskinbone     () { return m->nskinbone     ; }
  int  nskinbonevert () { return m->nskinbonevert ; }
  int  nhfield       () { return m->nhfield       ; }
  int  nhfielddata   () { return m->nhfielddata   ; }
  int  ntex          () { return m->ntex          ; }
  int  ntexdata      () { return m->ntexdata      ; }
  int  nmat          () { return m->nmat          ; }
  int  npair         () { return m->npair         ; }
  int  nexclude      () { return m->nexclude      ; }
  int  neq           () { return m->neq           ; }
  int  ntendon       () { return m->ntendon       ; }
  int  nwrap         () { return m->nwrap         ; }
  int  nsensor       () { return m->nsensor       ; }
  int  nnumeric      () { return m->nnumeric      ; }
  int  nnumericdata  () { return m->nnumericdata  ; }
  int  ntext         () { return m->ntext         ; }
  int  ntextdata     () { return m->ntextdata     ; }
  int  ntuple        () { return m->ntuple        ; }
  int  ntupledata    () { return m->ntupledata    ; }
  int  nkey          () { return m->nkey          ; }
  int  nmocap        () { return m->nmocap        ; }
  int  nplugin       () { return m->nplugin       ; }
  int  npluginattr   () { return m->npluginattr   ; }
  int  nuser_body    () { return m->nuser_body    ; }
  int  nuser_jnt     () { return m->nuser_jnt     ; }
  int  nuser_geom    () { return m->nuser_geom    ; }
  int  nuser_site    () { return m->nuser_site    ; }
  int  nuser_cam     () { return m->nuser_cam     ; }
  int  nuser_tendon  () { return m->nuser_tendon  ; }
  int  nuser_actuator() { return m->nuser_actuator; }
  int  nuser_sensor  () { return m->nuser_sensor  ; }
  int  nnames        () { return m->nnames        ; }
  int  nM            () { return m->nM            ; }
  int  nD            () { return m->nD            ; }
  int  nemax         () { return m->nemax         ; }
  int  njmax         () { return m->njmax         ; }
  int  nconmax       () { return m->nconmax       ; }
  int  nstack        () { return m->nstack        ; }
  int  nuserdata     () { return m->nuserdata     ; }
  int  nsensordata   () { return m->nsensordata   ; }
  int  npluginstate  () { return m->npluginstate  ; }
  int  nbuffer       () { return m->nbuffer       ; }
  val  qpos0                 () { return val(typed_memory_view(m->nq              * 1        , m->qpos0                  )); }
  val  qpos_spring           () { return val(typed_memory_view(m->nq              * 1        , m->qpos_spring            )); }
  val  body_parentid         () { return val(typed_memory_view(m->nbody           * 1        , m->body_parentid          )); }
  val  body_rootid           () { return val(typed_memory_view(m->nbody           * 1        , m->body_rootid            )); }
  val  body_weldid           () { return val(typed_memory_view(m->nbody           * 1        , m->body_weldid            )); }
  val  body_mocapid          () { return val(typed_memory_view(m->nbody           * 1        , m->body_mocapid           )); }
  val  body_jntnum           () { return val(typed_memory_view(m->nbody           * 1        , m->body_jntnum            )); }
  val  body_jntadr           () { return val(typed_memory_view(m->nbody           * 1        , m->body_jntadr            )); }
  val  body_dofnum           () { return val(typed_memory_view(m->nbody           * 1        , m->body_dofnum            )); }
  val  body_dofadr           () { return val(typed_memory_view(m->nbody           * 1        , m->body_dofadr            )); }
  val  body_geomnum          () { return val(typed_memory_view(m->nbody           * 1        , m->body_geomnum           )); }
  val  body_geomadr          () { return val(typed_memory_view(m->nbody           * 1        , m->body_geomadr           )); }
  val  body_simple           () { return val(typed_memory_view(m->nbody           * 1        , m->body_simple            )); }
  val  body_sameframe        () { return val(typed_memory_view(m->nbody           * 1        , m->body_sameframe         )); }
  val  body_pos              () { return val(typed_memory_view(m->nbody           * 3        , m->body_pos               )); }
  val  body_quat             () { return val(typed_memory_view(m->nbody           * 4        , m->body_quat              )); }
  val  body_ipos             () { return val(typed_memory_view(m->nbody           * 3        , m->body_ipos              )); }
  val  body_iquat            () { return val(typed_memory_view(m->nbody           * 4        , m->body_iquat             )); }
  val  body_mass             () { return val(typed_memory_view(m->nbody           * 1        , m->body_mass              )); }
  val  body_subtreemass      () { return val(typed_memory_view(m->nbody           * 1        , m->body_subtreemass       )); }
  val  body_inertia          () { return val(typed_memory_view(m->nbody           * 3        , m->body_inertia           )); }
  val  body_invweight0       () { return val(typed_memory_view(m->nbody           * 2        , m->body_invweight0        )); }
  val  body_gravcomp         () { return val(typed_memory_view(m->nbody           * 1        , m->body_gravcomp          )); }
  val  body_user             () { return val(typed_memory_view(m->nbody           * m->nuser_body, m->body_user              )); }
  val  body_plugin           () { return val(typed_memory_view(m->nbody           * 1        , m->body_plugin            )); }
  val  jnt_type              () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_type               )); }
  val  jnt_qposadr           () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_qposadr            )); }
  val  jnt_dofadr            () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_dofadr             )); }
  val  jnt_bodyid            () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_bodyid             )); }
  val  jnt_group             () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_group              )); }
  val  jnt_limited           () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_limited            )); }
  val  jnt_solref            () { return val(typed_memory_view(m->njnt            * mjNREF   , m->jnt_solref             )); }
  val  jnt_solimp            () { return val(typed_memory_view(m->njnt            * mjNIMP   , m->jnt_solimp             )); }
  val  jnt_pos               () { return val(typed_memory_view(m->njnt            * 3        , m->jnt_pos                )); }
  val  jnt_axis              () { return val(typed_memory_view(m->njnt            * 3        , m->jnt_axis               )); }
  val  jnt_stiffness         () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_stiffness          )); }
  val  jnt_range             () { return val(typed_memory_view(m->njnt            * 2        , m->jnt_range              )); }
  val  jnt_margin            () { return val(typed_memory_view(m->njnt            * 1        , m->jnt_margin             )); }
  val  jnt_user              () { return val(typed_memory_view(m->njnt            * m->nuser_jnt, m->jnt_user               )); }
  val  dof_bodyid            () { return val(typed_memory_view(m->nv              * 1        , m->dof_bodyid             )); }
  val  dof_jntid             () { return val(typed_memory_view(m->nv              * 1        , m->dof_jntid              )); }
  val  dof_parentid          () { return val(typed_memory_view(m->nv              * 1        , m->dof_parentid           )); }
  val  dof_Madr              () { return val(typed_memory_view(m->nv              * 1        , m->dof_Madr               )); }
  val  dof_simplenum         () { return val(typed_memory_view(m->nv              * 1        , m->dof_simplenum          )); }
  val  dof_solref            () { return val(typed_memory_view(m->nv              * mjNREF   , m->dof_solref             )); }
  val  dof_solimp            () { return val(typed_memory_view(m->nv              * mjNIMP   , m->dof_solimp             )); }
  val  dof_frictionloss      () { return val(typed_memory_view(m->nv              * 1        , m->dof_frictionloss       )); }
  val  dof_armature          () { return val(typed_memory_view(m->nv              * 1        , m->dof_armature           )); }
  val  dof_damping           () { return val(typed_memory_view(m->nv              * 1        , m->dof_damping            )); }
  val  dof_invweight0        () { return val(typed_memory_view(m->nv              * 1        , m->dof_invweight0         )); }
  val  dof_M0                () { return val(typed_memory_view(m->nv              * 1        , m->dof_M0                 )); }
  val  geom_type             () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_type              )); }
  val  geom_contype          () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_contype           )); }
  val  geom_conaffinity      () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_conaffinity       )); }
  val  geom_condim           () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_condim            )); }
  val  geom_bodyid           () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_bodyid            )); }
  val  geom_dataid           () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_dataid            )); }
  val  geom_matid            () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_matid             )); }
  val  geom_group            () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_group             )); }
  val  geom_priority         () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_priority          )); }
  val  geom_sameframe        () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_sameframe         )); }
  val  geom_solmix           () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_solmix            )); }
  val  geom_solref           () { return val(typed_memory_view(m->ngeom           * mjNREF   , m->geom_solref            )); }
  val  geom_solimp           () { return val(typed_memory_view(m->ngeom           * mjNIMP   , m->geom_solimp            )); }
  val  geom_size             () { return val(typed_memory_view(m->ngeom           * 3        , m->geom_size              )); }
  val  geom_rbound           () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_rbound            )); }
  val  geom_pos              () { return val(typed_memory_view(m->ngeom           * 3        , m->geom_pos               )); }
  val  geom_quat             () { return val(typed_memory_view(m->ngeom           * 4        , m->geom_quat              )); }
  val  geom_friction         () { return val(typed_memory_view(m->ngeom           * 3        , m->geom_friction          )); }
  val  geom_margin           () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_margin            )); }
  val  geom_gap              () { return val(typed_memory_view(m->ngeom           * 1        , m->geom_gap               )); }
  val  geom_fluid            () { return val(typed_memory_view(m->ngeom           * mjNFLUID , m->geom_fluid             )); }
  val  geom_user             () { return val(typed_memory_view(m->ngeom           * m->nuser_geom, m->geom_user              )); }
  val  geom_rgba             () { return val(typed_memory_view(m->ngeom           * 4        , m->geom_rgba              )); }
  val  site_type             () { return val(typed_memory_view(m->nsite           * 1        , m->site_type              )); }
  val  site_bodyid           () { return val(typed_memory_view(m->nsite           * 1        , m->site_bodyid            )); }
  val  site_matid            () { return val(typed_memory_view(m->nsite           * 1        , m->site_matid             )); }
  val  site_group            () { return val(typed_memory_view(m->nsite           * 1        , m->site_group             )); }
  val  site_sameframe        () { return val(typed_memory_view(m->nsite           * 1        , m->site_sameframe         )); }
  val  site_size             () { return val(typed_memory_view(m->nsite           * 3        , m->site_size              )); }
  val  site_pos              () { return val(typed_memory_view(m->nsite           * 3        , m->site_pos               )); }
  val  site_quat             () { return val(typed_memory_view(m->nsite           * 4        , m->site_quat              )); }
  val  site_user             () { return val(typed_memory_view(m->nsite           * m->nuser_site, m->site_user              )); }
  val  site_rgba             () { return val(typed_memory_view(m->nsite           * 4        , m->site_rgba              )); }
  val  cam_mode              () { return val(typed_memory_view(m->ncam            * 1        , m->cam_mode               )); }
  val  cam_bodyid            () { return val(typed_memory_view(m->ncam            * 1        , m->cam_bodyid             )); }
  val  cam_targetbodyid      () { return val(typed_memory_view(m->ncam            * 1        , m->cam_targetbodyid       )); }
  val  cam_pos               () { return val(typed_memory_view(m->ncam            * 3        , m->cam_pos                )); }
  val  cam_quat              () { return val(typed_memory_view(m->ncam            * 4        , m->cam_quat               )); }
  val  cam_poscom0           () { return val(typed_memory_view(m->ncam            * 3        , m->cam_poscom0            )); }
  val  cam_pos0              () { return val(typed_memory_view(m->ncam            * 3        , m->cam_pos0               )); }
  val  cam_mat0              () { return val(typed_memory_view(m->ncam            * 9        , m->cam_mat0               )); }
  val  cam_fovy              () { return val(typed_memory_view(m->ncam            * 1        , m->cam_fovy               )); }
  val  cam_ipd               () { return val(typed_memory_view(m->ncam            * 1        , m->cam_ipd                )); }
  val  cam_user              () { return val(typed_memory_view(m->ncam            * m->nuser_cam, m->cam_user               )); }
  val  light_mode            () { return val(typed_memory_view(m->nlight          * 1        , m->light_mode             )); }
  val  light_bodyid          () { return val(typed_memory_view(m->nlight          * 1        , m->light_bodyid           )); }
  val  light_targetbodyid    () { return val(typed_memory_view(m->nlight          * 1        , m->light_targetbodyid     )); }
  val  light_directional     () { return val(typed_memory_view(m->nlight          * 1        , m->light_directional      )); }
  val  light_castshadow      () { return val(typed_memory_view(m->nlight          * 1        , m->light_castshadow       )); }
  val  light_active          () { return val(typed_memory_view(m->nlight          * 1        , m->light_active           )); }
  val  light_pos             () { return val(typed_memory_view(m->nlight          * 3        , m->light_pos              )); }
  val  light_dir             () { return val(typed_memory_view(m->nlight          * 3        , m->light_dir              )); }
  val  light_poscom0         () { return val(typed_memory_view(m->nlight          * 3        , m->light_poscom0          )); }
  val  light_pos0            () { return val(typed_memory_view(m->nlight          * 3        , m->light_pos0             )); }
  val  light_dir0            () { return val(typed_memory_view(m->nlight          * 3        , m->light_dir0             )); }
  val  light_attenuation     () { return val(typed_memory_view(m->nlight          * 3        , m->light_attenuation      )); }
  val  light_cutoff          () { return val(typed_memory_view(m->nlight          * 1        , m->light_cutoff           )); }
  val  light_exponent        () { return val(typed_memory_view(m->nlight          * 1        , m->light_exponent         )); }
  val  light_ambient         () { return val(typed_memory_view(m->nlight          * 3        , m->light_ambient          )); }
  val  light_diffuse         () { return val(typed_memory_view(m->nlight          * 3        , m->light_diffuse          )); }
  val  light_specular        () { return val(typed_memory_view(m->nlight          * 3        , m->light_specular         )); }
  val  mesh_vertadr          () { return val(typed_memory_view(m->nmesh           * 1        , m->mesh_vertadr           )); }
  val  mesh_vertnum          () { return val(typed_memory_view(m->nmesh           * 1        , m->mesh_vertnum           )); }
  val  mesh_texcoordadr      () { return val(typed_memory_view(m->nmesh           * 1        , m->mesh_texcoordadr       )); }
  val  mesh_faceadr          () { return val(typed_memory_view(m->nmesh           * 1        , m->mesh_faceadr           )); }
  val  mesh_facenum          () { return val(typed_memory_view(m->nmesh           * 1        , m->mesh_facenum           )); }
  val  mesh_graphadr         () { return val(typed_memory_view(m->nmesh           * 1        , m->mesh_graphadr          )); }
  val  mesh_vert             () { return val(typed_memory_view(m->nmeshvert       * 3        , m->mesh_vert              )); }
  val  mesh_normal           () { return val(typed_memory_view(m->nmeshvert       * 3        , m->mesh_normal            )); }
  val  mesh_texcoord         () { return val(typed_memory_view(m->nmeshtexvert    * 2        , m->mesh_texcoord          )); }
  val  mesh_face             () { return val(typed_memory_view(m->nmeshface       * 3        , m->mesh_face              )); }
  val  mesh_graph            () { return val(typed_memory_view(m->nmeshgraph      * 1        , m->mesh_graph             )); }
  val  skin_matid            () { return val(typed_memory_view(m->nskin           * 1        , m->skin_matid             )); }
  val  skin_group            () { return val(typed_memory_view(m->nskin           * 1        , m->skin_group             )); }
  val  skin_rgba             () { return val(typed_memory_view(m->nskin           * 4        , m->skin_rgba              )); }
  val  skin_inflate          () { return val(typed_memory_view(m->nskin           * 1        , m->skin_inflate           )); }
  val  skin_vertadr          () { return val(typed_memory_view(m->nskin           * 1        , m->skin_vertadr           )); }
  val  skin_vertnum          () { return val(typed_memory_view(m->nskin           * 1        , m->skin_vertnum           )); }
  val  skin_texcoordadr      () { return val(typed_memory_view(m->nskin           * 1        , m->skin_texcoordadr       )); }
  val  skin_faceadr          () { return val(typed_memory_view(m->nskin           * 1        , m->skin_faceadr           )); }
  val  skin_facenum          () { return val(typed_memory_view(m->nskin           * 1        , m->skin_facenum           )); }
  val  skin_boneadr          () { return val(typed_memory_view(m->nskin           * 1        , m->skin_boneadr           )); }
  val  skin_bonenum          () { return val(typed_memory_view(m->nskin           * 1        , m->skin_bonenum           )); }
  val  skin_vert             () { return val(typed_memory_view(m->nskinvert       * 3        , m->skin_vert              )); }
  val  skin_texcoord         () { return val(typed_memory_view(m->nskintexvert    * 2        , m->skin_texcoord          )); }
  val  skin_face             () { return val(typed_memory_view(m->nskinface       * 3        , m->skin_face              )); }
  val  skin_bonevertadr      () { return val(typed_memory_view(m->nskinbone       * 1        , m->skin_bonevertadr       )); }
  val  skin_bonevertnum      () { return val(typed_memory_view(m->nskinbone       * 1        , m->skin_bonevertnum       )); }
  val  skin_bonebindpos      () { return val(typed_memory_view(m->nskinbone       * 3        , m->skin_bonebindpos       )); }
  val  skin_bonebindquat     () { return val(typed_memory_view(m->nskinbone       * 4        , m->skin_bonebindquat      )); }
  val  skin_bonebodyid       () { return val(typed_memory_view(m->nskinbone       * 1        , m->skin_bonebodyid        )); }
  val  skin_bonevertid       () { return val(typed_memory_view(m->nskinbonevert   * 1        , m->skin_bonevertid        )); }
  val  skin_bonevertweight   () { return val(typed_memory_view(m->nskinbonevert   * 1        , m->skin_bonevertweight    )); }
  val  hfield_size           () { return val(typed_memory_view(m->nhfield         * 4        , m->hfield_size            )); }
  val  hfield_nrow           () { return val(typed_memory_view(m->nhfield         * 1        , m->hfield_nrow            )); }
  val  hfield_ncol           () { return val(typed_memory_view(m->nhfield         * 1        , m->hfield_ncol            )); }
  val  hfield_adr            () { return val(typed_memory_view(m->nhfield         * 1        , m->hfield_adr             )); }
  val  hfield_data           () { return val(typed_memory_view(m->nhfielddata     * 1        , m->hfield_data            )); }
  val  tex_type              () { return val(typed_memory_view(m->ntex            * 1        , m->tex_type               )); }
  val  tex_height            () { return val(typed_memory_view(m->ntex            * 1        , m->tex_height             )); }
  val  tex_width             () { return val(typed_memory_view(m->ntex            * 1        , m->tex_width              )); }
  val  tex_adr               () { return val(typed_memory_view(m->ntex            * 1        , m->tex_adr                )); }
  val  tex_rgb               () { return val(typed_memory_view(m->ntexdata        * 1        , m->tex_rgb                )); }
  val  mat_texid             () { return val(typed_memory_view(m->nmat            * 1        , m->mat_texid              )); }
  val  mat_texuniform        () { return val(typed_memory_view(m->nmat            * 1        , m->mat_texuniform         )); }
  val  mat_texrepeat         () { return val(typed_memory_view(m->nmat            * 2        , m->mat_texrepeat          )); }
  val  mat_emission          () { return val(typed_memory_view(m->nmat            * 1        , m->mat_emission           )); }
  val  mat_specular          () { return val(typed_memory_view(m->nmat            * 1        , m->mat_specular           )); }
  val  mat_shininess         () { return val(typed_memory_view(m->nmat            * 1        , m->mat_shininess          )); }
  val  mat_reflectance       () { return val(typed_memory_view(m->nmat            * 1        , m->mat_reflectance        )); }
  val  mat_rgba              () { return val(typed_memory_view(m->nmat            * 4        , m->mat_rgba               )); }
  val  pair_dim              () { return val(typed_memory_view(m->npair           * 1        , m->pair_dim               )); }
  val  pair_geom1            () { return val(typed_memory_view(m->npair           * 1        , m->pair_geom1             )); }
  val  pair_geom2            () { return val(typed_memory_view(m->npair           * 1        , m->pair_geom2             )); }
  val  pair_signature        () { return val(typed_memory_view(m->npair           * 1        , m->pair_signature         )); }
  val  pair_solref           () { return val(typed_memory_view(m->npair           * mjNREF   , m->pair_solref            )); }
  val  pair_solimp           () { return val(typed_memory_view(m->npair           * mjNIMP   , m->pair_solimp            )); }
  val  pair_margin           () { return val(typed_memory_view(m->npair           * 1        , m->pair_margin            )); }
  val  pair_gap              () { return val(typed_memory_view(m->npair           * 1        , m->pair_gap               )); }
  val  pair_friction         () { return val(typed_memory_view(m->npair           * 5        , m->pair_friction          )); }
  val  exclude_signature     () { return val(typed_memory_view(m->nexclude        * 1        , m->exclude_signature      )); }
  val  eq_type               () { return val(typed_memory_view(m->neq             * 1        , m->eq_type                )); }
  val  eq_obj1id             () { return val(typed_memory_view(m->neq             * 1        , m->eq_obj1id              )); }
  val  eq_obj2id             () { return val(typed_memory_view(m->neq             * 1        , m->eq_obj2id              )); }
  val  eq_active             () { return val(typed_memory_view(m->neq             * 1        , m->eq_active              )); }
  val  eq_solref             () { return val(typed_memory_view(m->neq             * mjNREF   , m->eq_solref              )); }
  val  eq_solimp             () { return val(typed_memory_view(m->neq             * mjNIMP   , m->eq_solimp              )); }
  val  eq_data               () { return val(typed_memory_view(m->neq             * mjNEQDATA, m->eq_data                )); }
  val  tendon_adr            () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_adr             )); }
  val  tendon_num            () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_num             )); }
  val  tendon_matid          () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_matid           )); }
  val  tendon_group          () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_group           )); }
  val  tendon_limited        () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_limited         )); }
  val  tendon_width          () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_width           )); }
  val  tendon_solref_lim     () { return val(typed_memory_view(m->ntendon         * mjNREF   , m->tendon_solref_lim      )); }
  val  tendon_solimp_lim     () { return val(typed_memory_view(m->ntendon         * mjNIMP   , m->tendon_solimp_lim      )); }
  val  tendon_solref_fri     () { return val(typed_memory_view(m->ntendon         * mjNREF   , m->tendon_solref_fri      )); }
  val  tendon_solimp_fri     () { return val(typed_memory_view(m->ntendon         * mjNIMP   , m->tendon_solimp_fri      )); }
  val  tendon_range          () { return val(typed_memory_view(m->ntendon         * 2        , m->tendon_range           )); }
  val  tendon_margin         () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_margin          )); }
  val  tendon_stiffness      () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_stiffness       )); }
  val  tendon_damping        () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_damping         )); }
  val  tendon_frictionloss   () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_frictionloss    )); }
  val  tendon_lengthspring   () { return val(typed_memory_view(m->ntendon         * 2        , m->tendon_lengthspring    )); }
  val  tendon_length0        () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_length0         )); }
  val  tendon_invweight0     () { return val(typed_memory_view(m->ntendon         * 1        , m->tendon_invweight0      )); }
  val  tendon_user           () { return val(typed_memory_view(m->ntendon         * m->nuser_tendon, m->tendon_user            )); }
  val  tendon_rgba           () { return val(typed_memory_view(m->ntendon         * 4        , m->tendon_rgba            )); }
  val  wrap_type             () { return val(typed_memory_view(m->nwrap           * 1        , m->wrap_type              )); }
  val  wrap_objid            () { return val(typed_memory_view(m->nwrap           * 1        , m->wrap_objid             )); }
  val  wrap_prm              () { return val(typed_memory_view(m->nwrap           * 1        , m->wrap_prm               )); }
  val  actuator_trntype      () { return val(typed_memory_view(m->nu              * 1        , m->actuator_trntype       )); }
  val  actuator_dyntype      () { return val(typed_memory_view(m->nu              * 1        , m->actuator_dyntype       )); }
  val  actuator_gaintype     () { return val(typed_memory_view(m->nu              * 1        , m->actuator_gaintype      )); }
  val  actuator_biastype     () { return val(typed_memory_view(m->nu              * 1        , m->actuator_biastype      )); }
  val  actuator_trnid        () { return val(typed_memory_view(m->nu              * 2        , m->actuator_trnid         )); }
  val  actuator_actadr       () { return val(typed_memory_view(m->nu              * 1        , m->actuator_actadr        )); }
  val  actuator_actnum       () { return val(typed_memory_view(m->nu              * 1        , m->actuator_actnum        )); }
  val  actuator_group        () { return val(typed_memory_view(m->nu              * 1        , m->actuator_group         )); }
  val  actuator_ctrllimited  () { return val(typed_memory_view(m->nu              * 1        , m->actuator_ctrllimited   )); }
  val  actuator_forcelimited () { return val(typed_memory_view(m->nu              * 1        , m->actuator_forcelimited  )); }
  val  actuator_actlimited   () { return val(typed_memory_view(m->nu              * 1        , m->actuator_actlimited    )); }
  val  actuator_dynprm       () { return val(typed_memory_view(m->nu              * mjNDYN   , m->actuator_dynprm        )); }
  val  actuator_gainprm      () { return val(typed_memory_view(m->nu              * mjNGAIN  , m->actuator_gainprm       )); }
  val  actuator_biasprm      () { return val(typed_memory_view(m->nu              * mjNBIAS  , m->actuator_biasprm       )); }
  val  actuator_ctrlrange    () { return val(typed_memory_view(m->nu              * 2        , m->actuator_ctrlrange     )); }
  val  actuator_forcerange   () { return val(typed_memory_view(m->nu              * 2        , m->actuator_forcerange    )); }
  val  actuator_actrange     () { return val(typed_memory_view(m->nu              * 2        , m->actuator_actrange      )); }
  val  actuator_gear         () { return val(typed_memory_view(m->nu              * 6        , m->actuator_gear          )); }
  val  actuator_cranklength  () { return val(typed_memory_view(m->nu              * 1        , m->actuator_cranklength   )); }
  val  actuator_acc0         () { return val(typed_memory_view(m->nu              * 1        , m->actuator_acc0          )); }
  val  actuator_length0      () { return val(typed_memory_view(m->nu              * 1        , m->actuator_length0       )); }
  val  actuator_lengthrange  () { return val(typed_memory_view(m->nu              * 2        , m->actuator_lengthrange   )); }
  val  actuator_user         () { return val(typed_memory_view(m->nu              * m->nuser_actuator, m->actuator_user          )); }
  val  actuator_plugin       () { return val(typed_memory_view(m->nu              * 1        , m->actuator_plugin        )); }
  val  sensor_type           () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_type            )); }
  val  sensor_datatype       () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_datatype        )); }
  val  sensor_needstage      () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_needstage       )); }
  val  sensor_objtype        () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_objtype         )); }
  val  sensor_objid          () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_objid           )); }
  val  sensor_reftype        () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_reftype         )); }
  val  sensor_refid          () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_refid           )); }
  val  sensor_dim            () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_dim             )); }
  val  sensor_adr            () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_adr             )); }
  val  sensor_cutoff         () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_cutoff          )); }
  val  sensor_noise          () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_noise           )); }
  val  sensor_user           () { return val(typed_memory_view(m->nsensor         * m->nuser_sensor, m->sensor_user            )); }
  val  sensor_plugin         () { return val(typed_memory_view(m->nsensor         * 1        , m->sensor_plugin          )); }
  val  plugin                () { return val(typed_memory_view(m->nplugin         * 1        , m->plugin                 )); }
  val  plugin_stateadr       () { return val(typed_memory_view(m->nplugin         * 1        , m->plugin_stateadr        )); }
  val  plugin_statenum       () { return val(typed_memory_view(m->nplugin         * 1        , m->plugin_statenum        )); }
  val  plugin_attr           () { return val(typed_memory_view(m->npluginattr     * 1        , m->plugin_attr            )); }
  val  plugin_attradr        () { return val(typed_memory_view(m->nplugin         * 1        , m->plugin_attradr         )); }
  val  numeric_adr           () { return val(typed_memory_view(m->nnumeric        * 1        , m->numeric_adr            )); }
  val  numeric_size          () { return val(typed_memory_view(m->nnumeric        * 1        , m->numeric_size           )); }
  val  numeric_data          () { return val(typed_memory_view(m->nnumericdata    * 1        , m->numeric_data           )); }
  val  text_adr              () { return val(typed_memory_view(m->ntext           * 1        , m->text_adr               )); }
  val  text_size             () { return val(typed_memory_view(m->ntext           * 1        , m->text_size              )); }
  val  text_data             () { return val(typed_memory_view(m->ntextdata       * 1        , m->text_data              )); }
  val  tuple_adr             () { return val(typed_memory_view(m->ntuple          * 1        , m->tuple_adr              )); }
  val  tuple_size            () { return val(typed_memory_view(m->ntuple          * 1        , m->tuple_size             )); }
  val  tuple_objtype         () { return val(typed_memory_view(m->ntupledata      * 1        , m->tuple_objtype          )); }
  val  tuple_objid           () { return val(typed_memory_view(m->ntupledata      * 1        , m->tuple_objid            )); }
  val  tuple_objprm          () { return val(typed_memory_view(m->ntupledata      * 1        , m->tuple_objprm           )); }
  val  key_time              () { return val(typed_memory_view(m->nkey            * 1        , m->key_time               )); }
  val  key_qpos              () { return val(typed_memory_view(m->nkey            * m->nq    , m->key_qpos               )); }
  val  key_qvel              () { return val(typed_memory_view(m->nkey            * m->nv    , m->key_qvel               )); }
  val  key_act               () { return val(typed_memory_view(m->nkey            * m->na    , m->key_act                )); }
  val  key_mpos              () { return val(typed_memory_view(m->nkey            * m->nmocap, m->key_mpos               )); }
  val  key_mquat             () { return val(typed_memory_view(m->nkey            * m->nmocap, m->key_mquat              )); }
  val  key_ctrl              () { return val(typed_memory_view(m->nkey            * m->nu    , m->key_ctrl               )); }
  val  name_bodyadr          () { return val(typed_memory_view(m->nbody           * 1        , m->name_bodyadr           )); }
  val  name_jntadr           () { return val(typed_memory_view(m->njnt            * 1        , m->name_jntadr            )); }
  val  name_geomadr          () { return val(typed_memory_view(m->ngeom           * 1        , m->name_geomadr           )); }
  val  name_siteadr          () { return val(typed_memory_view(m->nsite           * 1        , m->name_siteadr           )); }
  val  name_camadr           () { return val(typed_memory_view(m->ncam            * 1        , m->name_camadr            )); }
  val  name_lightadr         () { return val(typed_memory_view(m->nlight          * 1        , m->name_lightadr          )); }
  val  name_meshadr          () { return val(typed_memory_view(m->nmesh           * 1        , m->name_meshadr           )); }
  val  name_skinadr          () { return val(typed_memory_view(m->nskin           * 1        , m->name_skinadr           )); }
  val  name_hfieldadr        () { return val(typed_memory_view(m->nhfield         * 1        , m->name_hfieldadr         )); }
  val  name_texadr           () { return val(typed_memory_view(m->ntex            * 1        , m->name_texadr            )); }
  val  name_matadr           () { return val(typed_memory_view(m->nmat            * 1        , m->name_matadr            )); }
  val  name_pairadr          () { return val(typed_memory_view(m->npair           * 1        , m->name_pairadr           )); }
  val  name_excludeadr       () { return val(typed_memory_view(m->nexclude        * 1        , m->name_excludeadr        )); }
  val  name_eqadr            () { return val(typed_memory_view(m->neq             * 1        , m->name_eqadr             )); }
  val  name_tendonadr        () { return val(typed_memory_view(m->ntendon         * 1        , m->name_tendonadr         )); }
  val  name_actuatoradr      () { return val(typed_memory_view(m->nu              * 1        , m->name_actuatoradr       )); }
  val  name_sensoradr        () { return val(typed_memory_view(m->nsensor         * 1        , m->name_sensoradr         )); }
  val  name_numericadr       () { return val(typed_memory_view(m->nnumeric        * 1        , m->name_numericadr        )); }
  val  name_textadr          () { return val(typed_memory_view(m->ntext           * 1        , m->name_textadr           )); }
  val  name_tupleadr         () { return val(typed_memory_view(m->ntuple          * 1        , m->name_tupleadr          )); }
  val  name_keyadr           () { return val(typed_memory_view(m->nkey            * 1        , m->name_keyadr            )); }
  val  name_pluginadr        () { return val(typed_memory_view(m->nplugin         * 1        , m->name_pluginadr         )); }
  val  names                 () { return val(typed_memory_view(m->nnames          * 1        , m->names                  )); }

private:
  mjModel *m;
};

class State {
public:
  State(Model m)  { d = mj_makeData(m.ptr()); }
  mjData *ptr  () { return d; }
  mjData getVal() { return *d; }

private:
  mjData *d;
};

class Simulation {
public:
  Simulation(Model *m, State *s) {
    _model = m;
    _state = s;
  }

  State *state() { return _state; }
  Model *model() { return _model; }

  void applyForce(
    mjtNum fx, mjtNum fy, mjtNum fz, 
    mjtNum tx, mjtNum ty, mjtNum tz,  
    mjtNum px, mjtNum py, mjtNum pz, int body) {
    mjtNum force [3] = {fx, fy, fz};
    mjtNum torque[3] = {tx, ty, tz};
    mjtNum point [3] = {px, py, pz};
    mj_applyFT(_model->ptr(), _state->ptr(), 
               force, torque, point, body, 
               _state->ptr()->qfrc_applied);
  }

  // copied from the source of mjv_applyPerturbPose
  // sets perturb pos,quat in d->mocap when selected body is mocap, and in d->qpos otherwise
  //  d->qpos written only if flg_paused and subtree root for selected body has free joint
  void applyPose(int bodyID,
                 mjtNum refPosX,  mjtNum refPosY,  mjtNum refPosZ,
                 mjtNum refQuat1, mjtNum refQuat2, mjtNum refQuat3, mjtNum refQuat4,
                 int flg_paused) {
    int rootid = 0, sel = bodyID;//pert->select;
    mjtNum pos1[3], quat1[4], pos2[3], quat2[4], refpos[3], refquat[4];
    mjtNum *Rpos, *Rquat, *Cpos, *Cquat;
    mjtNum inrefpos [3] = { refPosX , refPosY , refPosZ };
    mjtNum inrefquat[4] = { refQuat1, refQuat2, refQuat3, refQuat4 };
    mjModel *m = _model->ptr();
    mjData  *d = _state->ptr();

    // exit if nothing to do
    //if (sel<=0 || sel>=m->nbody || !(pert->active | pert->active2)) { return; }

    // get rootid above selected body
    rootid = m->body_rootid[sel];

    // transform refpos,refquat from I-frame to X-frame of body[sel]
    mju_negPose(pos1, quat1, m->body_ipos+3*sel, m->body_iquat+4*sel);
    mju_mulPose(refpos, refquat, inrefpos, inrefquat, pos1, quat1);

    // mocap body
    if (m->body_mocapid[sel]>=0) {
      // copy ref pose into mocap pose
      mju_copy3(d->mocap_pos + 3*m->body_mocapid[sel], refpos);
      mju_copy4(d->mocap_quat + 4*m->body_mocapid[sel], refquat);
    }

    // floating body, paused
    else if (flg_paused && m->body_jntnum[sel]==1 &&
            m->jnt_type[m->body_jntadr[sel]]==mjJNT_FREE) {
      // copy ref pose into qpos
      mju_copy3(d->qpos + m->jnt_qposadr[m->body_jntadr[sel]], refpos);
      mju_copy4(d->qpos + m->jnt_qposadr[m->body_jntadr[sel]] + 3, refquat);
    }

    // child of floating body, paused
    else if (flg_paused && m->body_jntnum[rootid]==1 &&
            m->jnt_type[m->body_jntadr[rootid]]==mjJNT_FREE) {
      // get pointers to root
      Rpos = d->qpos + m->jnt_qposadr[m->body_jntadr[rootid]];
      Rquat = Rpos + 3;

      // get pointers to child
      Cpos = d->xpos + 3*sel;
      Cquat = d->xquat + 4*sel;

      // set root <- ref*neg(child)*root
      mju_negPose(pos1, quat1, Cpos, Cquat);                      // neg(child)
      mju_mulPose(pos2, quat2, pos1, quat1, Rpos, Rquat);         // neg(child)*root
      mju_mulPose(Rpos, Rquat, refpos, refquat, pos2, quat2);     // ref*neg(child)*root
    }
  }

  // MJDATA_DEFINITIONS
  val  qpos                  () { return val(typed_memory_view(_model->ptr()->nq              * 1        , _state->ptr()->qpos                   )); }
  val  qvel                  () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->qvel                   )); }
  val  act                   () { return val(typed_memory_view(_model->ptr()->na              * 1        , _state->ptr()->act                    )); }
  val  qacc_warmstart        () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->qacc_warmstart         )); }
  val  plugin_state          () { return val(typed_memory_view(_model->ptr()->npluginstate    * 1        , _state->ptr()->plugin_state           )); }
  val  ctrl                  () { return val(typed_memory_view(_model->ptr()->nu              * 1        , _state->ptr()->ctrl                   )); }
  val  qfrc_applied          () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->qfrc_applied           )); }
  val  xfrc_applied          () { return val(typed_memory_view(_model->ptr()->nbody           * 6        , _state->ptr()->xfrc_applied           )); }
  val  mocap_pos             () { return val(typed_memory_view(_model->ptr()->nmocap          * 3        , _state->ptr()->mocap_pos              )); }
  val  mocap_quat            () { return val(typed_memory_view(_model->ptr()->nmocap          * 4        , _state->ptr()->mocap_quat             )); }
  val  qacc                  () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->qacc                   )); }
  val  act_dot               () { return val(typed_memory_view(_model->ptr()->na              * 1        , _state->ptr()->act_dot                )); }
  val  userdata              () { return val(typed_memory_view(_model->ptr()->nuserdata       * 1        , _state->ptr()->userdata               )); }
  val  sensordata            () { return val(typed_memory_view(_model->ptr()->nsensordata     * 1        , _state->ptr()->sensordata             )); }
  val  plugin                () { return val(typed_memory_view(_model->ptr()->nplugin         * 1        , _state->ptr()->plugin                 )); }
  val  plugin_data           () { return val(typed_memory_view(_model->ptr()->nplugin         * 1        , _state->ptr()->plugin_data            )); }
  val  xpos                  () { return val(typed_memory_view(_model->ptr()->nbody           * 3        , _state->ptr()->xpos                   )); }
  val  xquat                 () { return val(typed_memory_view(_model->ptr()->nbody           * 4        , _state->ptr()->xquat                  )); }
  val  xmat                  () { return val(typed_memory_view(_model->ptr()->nbody           * 9        , _state->ptr()->xmat                   )); }
  val  xipos                 () { return val(typed_memory_view(_model->ptr()->nbody           * 3        , _state->ptr()->xipos                  )); }
  val  ximat                 () { return val(typed_memory_view(_model->ptr()->nbody           * 9        , _state->ptr()->ximat                  )); }
  val  xanchor               () { return val(typed_memory_view(_model->ptr()->njnt            * 3        , _state->ptr()->xanchor                )); }
  val  xaxis                 () { return val(typed_memory_view(_model->ptr()->njnt            * 3        , _state->ptr()->xaxis                  )); }
  val  geom_xpos             () { return val(typed_memory_view(_model->ptr()->ngeom           * 3        , _state->ptr()->geom_xpos              )); }
  val  geom_xmat             () { return val(typed_memory_view(_model->ptr()->ngeom           * 9        , _state->ptr()->geom_xmat              )); }
  val  site_xpos             () { return val(typed_memory_view(_model->ptr()->nsite           * 3        , _state->ptr()->site_xpos              )); }
  val  site_xmat             () { return val(typed_memory_view(_model->ptr()->nsite           * 9        , _state->ptr()->site_xmat              )); }
  val  cam_xpos              () { return val(typed_memory_view(_model->ptr()->ncam            * 3        , _state->ptr()->cam_xpos               )); }
  val  cam_xmat              () { return val(typed_memory_view(_model->ptr()->ncam            * 9        , _state->ptr()->cam_xmat               )); }
  val  light_xpos            () { return val(typed_memory_view(_model->ptr()->nlight          * 3        , _state->ptr()->light_xpos             )); }
  val  light_xdir            () { return val(typed_memory_view(_model->ptr()->nlight          * 3        , _state->ptr()->light_xdir             )); }
  val  subtree_com           () { return val(typed_memory_view(_model->ptr()->nbody           * 3        , _state->ptr()->subtree_com            )); }
  val  cdof                  () { return val(typed_memory_view(_model->ptr()->nv              * 6        , _state->ptr()->cdof                   )); }
  val  cinert                () { return val(typed_memory_view(_model->ptr()->nbody           * 10       , _state->ptr()->cinert                 )); }
  val  ten_wrapadr           () { return val(typed_memory_view(_model->ptr()->ntendon         * 1        , _state->ptr()->ten_wrapadr            )); }
  val  ten_wrapnum           () { return val(typed_memory_view(_model->ptr()->ntendon         * 1        , _state->ptr()->ten_wrapnum            )); }
  val  ten_J_rownnz          () { return val(typed_memory_view(_model->ptr()->ntendon         * 1        , _state->ptr()->ten_J_rownnz           )); }
  val  ten_J_rowadr          () { return val(typed_memory_view(_model->ptr()->ntendon         * 1        , _state->ptr()->ten_J_rowadr           )); }
  val  ten_J_colind          () { return val(typed_memory_view(_model->ptr()->ntendon         * _model->ptr()->nv, _state->ptr()->ten_J_colind           )); }
  val  ten_length            () { return val(typed_memory_view(_model->ptr()->ntendon         * 1        , _state->ptr()->ten_length             )); }
  val  ten_J                 () { return val(typed_memory_view(_model->ptr()->ntendon         * _model->ptr()->nv, _state->ptr()->ten_J                  )); }
  val  wrap_obj              () { return val(typed_memory_view(_model->ptr()->nwrap           * 2        , _state->ptr()->wrap_obj               )); }
  val  wrap_xpos             () { return val(typed_memory_view(_model->ptr()->nwrap           * 6        , _state->ptr()->wrap_xpos              )); }
  val  actuator_length       () { return val(typed_memory_view(_model->ptr()->nu              * 1        , _state->ptr()->actuator_length        )); }
  val  actuator_moment       () { return val(typed_memory_view(_model->ptr()->nu              * _model->ptr()->nv, _state->ptr()->actuator_moment        )); }
  val  crb                   () { return val(typed_memory_view(_model->ptr()->nbody           * 10       , _state->ptr()->crb                    )); }
  val  qM                    () { return val(typed_memory_view(_model->ptr()->nM              * 1        , _state->ptr()->qM                     )); }
  val  qLD                   () { return val(typed_memory_view(_model->ptr()->nM              * 1        , _state->ptr()->qLD                    )); }
  val  qLDiagInv             () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->qLDiagInv              )); }
  val  qLDiagSqrtInv         () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->qLDiagSqrtInv          )); }
  val  ten_velocity          () { return val(typed_memory_view(_model->ptr()->ntendon         * 1        , _state->ptr()->ten_velocity           )); }
  val  actuator_velocity     () { return val(typed_memory_view(_model->ptr()->nu              * 1        , _state->ptr()->actuator_velocity      )); }
  val  cvel                  () { return val(typed_memory_view(_model->ptr()->nbody           * 6        , _state->ptr()->cvel                   )); }
  val  cdof_dot              () { return val(typed_memory_view(_model->ptr()->nv              * 6        , _state->ptr()->cdof_dot               )); }
  val  qfrc_bias             () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->qfrc_bias              )); }
  val  qfrc_passive          () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->qfrc_passive           )); }
  val  subtree_linvel        () { return val(typed_memory_view(_model->ptr()->nbody           * 3        , _state->ptr()->subtree_linvel         )); }
  val  subtree_angmom        () { return val(typed_memory_view(_model->ptr()->nbody           * 3        , _state->ptr()->subtree_angmom         )); }
  val  qH                    () { return val(typed_memory_view(_model->ptr()->nM              * 1        , _state->ptr()->qH                     )); }
  val  qHDiagInv             () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->qHDiagInv              )); }
  val  D_rownnz              () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->D_rownnz               )); }
  val  D_rowadr              () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->D_rowadr               )); }
  val  D_colind              () { return val(typed_memory_view(_model->ptr()->nD              * 1        , _state->ptr()->D_colind               )); }
  val  qDeriv                () { return val(typed_memory_view(_model->ptr()->nD              * 1        , _state->ptr()->qDeriv                 )); }
  val  qLU                   () { return val(typed_memory_view(_model->ptr()->nD              * 1        , _state->ptr()->qLU                    )); }
  val  actuator_force        () { return val(typed_memory_view(_model->ptr()->nu              * 1        , _state->ptr()->actuator_force         )); }
  val  qfrc_actuator         () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->qfrc_actuator          )); }
  val  qfrc_smooth           () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->qfrc_smooth            )); }
  val  qacc_smooth           () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->qacc_smooth            )); }
  val  qfrc_constraint       () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->qfrc_constraint        )); }
  val  qfrc_inverse          () { return val(typed_memory_view(_model->ptr()->nv              * 1        , _state->ptr()->qfrc_inverse           )); }
  val  cacc                  () { return val(typed_memory_view(_model->ptr()->nbody           * 6        , _state->ptr()->cacc                   )); }
  val  cfrc_int              () { return val(typed_memory_view(_model->ptr()->nbody           * 6        , _state->ptr()->cfrc_int               )); }
  val  cfrc_ext              () { return val(typed_memory_view(_model->ptr()->nbody           * 6        , _state->ptr()->cfrc_ext               )); }
  void   freeLastXML         (                    ) { return mj_freeLastXML              (                    ); }
  void   step                (                    ) { return mj_step                     (_model->ptr(), _state->ptr()); }
  void   step1               (                    ) { return mj_step1                    (_model->ptr(), _state->ptr()); }
  void   step2               (                    ) { return mj_step2                    (_model->ptr(), _state->ptr()); }
  void   forward             (                    ) { return mj_forward                  (_model->ptr(), _state->ptr()); }
  void   inverse             (                    ) { return mj_inverse                  (_model->ptr(), _state->ptr()); }
  void   forwardSkip         (int skipstage, int skipsensor) { return mj_forwardSkip              (_model->ptr(), _state->ptr(), skipstage, skipsensor); }
  void   inverseSkip         (int skipstage, int skipsensor) { return mj_inverseSkip              (_model->ptr(), _state->ptr(), skipstage, skipsensor); }
  void   defaultSolRefImp    (mjtNum * solref, mjtNum * solimp) { return mj_defaultSolRefImp         (solref, solimp      ); }
  int    sizeModel           (                    ) { return mj_sizeModel                (_model->ptr()       ); }
  void   resetData           (                    ) { return mj_resetData                (_model->ptr(), _state->ptr()); }
  void   resetDataDebug      (unsigned char debug_value) { return mj_resetDataDebug           (_model->ptr(), _state->ptr(), debug_value); }
  void   resetDataKeyframe   (int key             ) { return mj_resetDataKeyframe        (_model->ptr(), _state->ptr(), key); }
  void   deleteData          (                    ) { return mj_deleteData               (_state->ptr()       ); }
  void   resetCallbacks      (                    ) { return mj_resetCallbacks           (                    ); }
  void   printFormattedModel (std::string filename, std::string float_format) { return mj_printFormattedModel      (_model->ptr(), filename.c_str(), float_format.c_str()); }
  void   printModel          (std::string filename) { return mj_printModel               (_model->ptr(), filename.c_str()); }
  void   printFormattedData  (std::string filename, std::string float_format) { return mj_printFormattedData       (_model->ptr(), _state->ptr(), filename.c_str(), float_format.c_str()); }
  void   printData           (std::string filename) { return mj_printData                (_model->ptr(), _state->ptr(), filename.c_str()); }
  void   _printMat           (const mjtNum * mat, int nr, int nc) { return mju_printMat                (mat, nr, nc         ); }
  void   fwdPosition         (                    ) { return mj_fwdPosition              (_model->ptr(), _state->ptr()); }
  void   fwdVelocity         (                    ) { return mj_fwdVelocity              (_model->ptr(), _state->ptr()); }
  void   fwdActuation        (                    ) { return mj_fwdActuation             (_model->ptr(), _state->ptr()); }
  void   fwdAcceleration     (                    ) { return mj_fwdAcceleration          (_model->ptr(), _state->ptr()); }
  void   fwdConstraint       (                    ) { return mj_fwdConstraint            (_model->ptr(), _state->ptr()); }
  void   Euler               (                    ) { return mj_Euler                    (_model->ptr(), _state->ptr()); }
  void   RungeKutta          (int N               ) { return mj_RungeKutta               (_model->ptr(), _state->ptr(), N); }
  void   invPosition         (                    ) { return mj_invPosition              (_model->ptr(), _state->ptr()); }
  void   invVelocity         (                    ) { return mj_invVelocity              (_model->ptr(), _state->ptr()); }
  void   invConstraint       (                    ) { return mj_invConstraint            (_model->ptr(), _state->ptr()); }
  void   compareFwdInv       (                    ) { return mj_compareFwdInv            (_model->ptr(), _state->ptr()); }
  void   sensorPos           (                    ) { return mj_sensorPos                (_model->ptr(), _state->ptr()); }
  void   sensorVel           (                    ) { return mj_sensorVel                (_model->ptr(), _state->ptr()); }
  void   sensorAcc           (                    ) { return mj_sensorAcc                (_model->ptr(), _state->ptr()); }
  void   energyPos           (                    ) { return mj_energyPos                (_model->ptr(), _state->ptr()); }
  void   energyVel           (                    ) { return mj_energyVel                (_model->ptr(), _state->ptr()); }
  void   checkPos            (                    ) { return mj_checkPos                 (_model->ptr(), _state->ptr()); }
  void   checkVel            (                    ) { return mj_checkVel                 (_model->ptr(), _state->ptr()); }
  void   checkAcc            (                    ) { return mj_checkAcc                 (_model->ptr(), _state->ptr()); }
  void   kinematics          (                    ) { return mj_kinematics               (_model->ptr(), _state->ptr()); }
  void   comPos              (                    ) { return mj_comPos                   (_model->ptr(), _state->ptr()); }
  void   camlight            (                    ) { return mj_camlight                 (_model->ptr(), _state->ptr()); }
  void   tendon              (                    ) { return mj_tendon                   (_model->ptr(), _state->ptr()); }
  void   transmission        (                    ) { return mj_transmission             (_model->ptr(), _state->ptr()); }
  void   crbCalculate        (                    ) { return mj_crb                      (_model->ptr(), _state->ptr()); }
  void   factorM             (                    ) { return mj_factorM                  (_model->ptr(), _state->ptr()); }
  void   solveM              (mjtNum * x, const mjtNum * y, int n) { return mj_solveM                   (_model->ptr(), _state->ptr(), x, y, n); }
  void   solveM2             (mjtNum * x, const mjtNum * y, int n) { return mj_solveM2                  (_model->ptr(), _state->ptr(), x, y, n); }
  void   comVel              (                    ) { return mj_comVel                   (_model->ptr(), _state->ptr()); }
  void   passive             (                    ) { return mj_passive                  (_model->ptr(), _state->ptr()); }
  void   subtreeVel          (                    ) { return mj_subtreeVel               (_model->ptr(), _state->ptr()); }
  void   rne                 (int flg_acc, mjtNum * result) { return mj_rne                      (_model->ptr(), _state->ptr(), flg_acc, result); }
  void   rnePostConstraint   (                    ) { return mj_rnePostConstraint        (_model->ptr(), _state->ptr()); }
  void   collision           (                    ) { return mj_collision                (_model->ptr(), _state->ptr()); }
  void   makeConstraint      (                    ) { return mj_makeConstraint           (_model->ptr(), _state->ptr()); }
  void   projectConstraint   (                    ) { return mj_projectConstraint        (_model->ptr(), _state->ptr()); }
  void   referenceConstraint (                    ) { return mj_referenceConstraint      (_model->ptr(), _state->ptr()); }
  int    isPyramidal         (                    ) { return mj_isPyramidal              (_model->ptr()       ); }
  int    isSparse            (                    ) { return mj_isSparse                 (_model->ptr()       ); }
  int    isDual              (                    ) { return mj_isDual                   (_model->ptr()       ); }
  void   mulJacVec           (mjtNum * res, const mjtNum * vec) { return mj_mulJacVec                (_model->ptr(), _state->ptr(), res, vec); }
  void   mulJacTVec          (mjtNum * res, const mjtNum * vec) { return mj_mulJacTVec               (_model->ptr(), _state->ptr(), res, vec); }
  void   jacSubtreeCom       (mjtNum * jacp, int body) { return mj_jacSubtreeCom            (_model->ptr(), _state->ptr(), jacp, body); }
  int    name2id             (int type, std::string name) { return mj_name2id                  (_model->ptr(), type, name.c_str()); }
  std::string id2name             (int type, int id    ) { return std::string(mj_id2name                  (_model->ptr(), type, id)); }
  void   fullM               (mjtNum * dst, const mjtNum * M) { return mj_fullM                    (_model->ptr(), dst, M); }
  void   differentiatePos    (mjtNum * qvel, mjtNum dt, const mjtNum * qpos1, const mjtNum * qpos2) { return mj_differentiatePos         (_model->ptr(), qvel, dt, qpos1, qpos2); }
  void   integratePos        (mjtNum * qpos, const mjtNum * qvel, mjtNum dt) { return mj_integratePos             (_model->ptr(), qpos, qvel, dt); }
  void   normalizeQuat       (mjtNum * qpos       ) { return mj_normalizeQuat            (_model->ptr(), qpos ); }
  mjtNum getTotalmass        (                    ) { return mj_getTotalmass             (_model->ptr()       ); }
  std::string getPluginConfig     (int plugin_id, std::string attrib) { return std::string(mj_getPluginConfig          (_model->ptr(), plugin_id, attrib.c_str())); }
  void   loadPluginLibrary   (std::string path    ) { return mj_loadPluginLibrary        (path.c_str()        ); }
  int    version             (                    ) { return mj_version                  (                    ); }
  std::string versionString       (                    ) { return std::string(mj_versionString            (                    )); }
  void   _rectangle          (mjrRect viewport, float r, float g, float b, float a) { return mjr_rectangle               (viewport, r, g, b, a); }
  void   _finish             (                    ) { return mjr_finish                  (                    ); }
  int    _getError           (                    ) { return mjr_getError                (                    ); }
  mjuiThemeSpacing i_themeSpacing      (int ind             ) { return mjui_themeSpacing           (ind                 ); }
  mjuiThemeColor i_themeColor        (int ind             ) { return mjui_themeColor             (ind                 ); }
  void   _error              (std::string msg     ) { return mju_error                   (msg.c_str()         ); }
  void   _error_i            (std::string msg, int i) { return mju_error_i                 (msg.c_str(), i      ); }
  void   _error_s            (std::string msg, std::string text) { return mju_error_s                 (msg.c_str(), text.c_str()); }
  void   _warning            (std::string msg     ) { return mju_warning                 (msg.c_str()         ); }
  void   _warning_i          (std::string msg, int i) { return mju_warning_i               (msg.c_str(), i      ); }
  void   _warning_s          (std::string msg, std::string text) { return mju_warning_s               (msg.c_str(), text.c_str()); }
  void   _clearHandlers      (                    ) { return mju_clearHandlers           (                    ); }
  void   warning             (int warning, int info) { return mj_warning                  (_state->ptr(), warning, info); }
  void   _writeLog           (std::string type, std::string msg) { return mju_writeLog                (type.c_str(), msg.c_str()); }
  int    activate            (std::string filename) { return mj_activate                 (filename.c_str()    ); }
  void   deactivate          (                    ) { return mj_deactivate               (                    ); }
  void   _zero               (mjtNum * res, int n ) { return mju_zero                    (res, n              ); }
  void   _fill               (mjtNum * res, mjtNum val, int n) { return mju_fill                    (res, val, n         ); }
  void   _copy               (mjtNum * res, const mjtNum * data, int n) { return mju_copy                    (res, data, n        ); }
  mjtNum _sum                (const mjtNum * vec, int n) { return mju_sum                     (vec, n              ); }
  mjtNum _L1                 (const mjtNum * vec, int n) { return mju_L1                      (vec, n              ); }
  void   _scl                (mjtNum * res, const mjtNum * vec, mjtNum scl, int n) { return mju_scl                     (res, vec, scl, n    ); }
  void   _add                (mjtNum * res, const mjtNum * vec1, const mjtNum * vec2, int n) { return mju_add                     (res, vec1, vec2, n  ); }
  void   _sub                (mjtNum * res, const mjtNum * vec1, const mjtNum * vec2, int n) { return mju_sub                     (res, vec1, vec2, n  ); }
  void   _addTo              (mjtNum * res, const mjtNum * vec, int n) { return mju_addTo                   (res, vec, n         ); }
  void   _subFrom            (mjtNum * res, const mjtNum * vec, int n) { return mju_subFrom                 (res, vec, n         ); }
  void   _addToScl           (mjtNum * res, const mjtNum * vec, mjtNum scl, int n) { return mju_addToScl                (res, vec, scl, n    ); }
  void   _addScl             (mjtNum * res, const mjtNum * vec1, const mjtNum * vec2, mjtNum scl, int n) { return mju_addScl                  (res, vec1, vec2, scl, n); }
  mjtNum _normalize          (mjtNum * res, int n ) { return mju_normalize               (res, n              ); }
  mjtNum _norm               (const mjtNum * res, int n) { return mju_norm                    (res, n              ); }
  mjtNum _dot                (const mjtNum * vec1, const mjtNum * vec2, int n) { return mju_dot                     (vec1, vec2, n       ); }
  void   _mulMatVec          (mjtNum * res, const mjtNum * mat, const mjtNum * vec, int nr, int nc) { return mju_mulMatVec               (res, mat, vec, nr, nc); }
  void   _mulMatTVec         (mjtNum * res, const mjtNum * mat, const mjtNum * vec, int nr, int nc) { return mju_mulMatTVec              (res, mat, vec, nr, nc); }
  mjtNum _mulVecMatVec       (const mjtNum * vec1, const mjtNum * mat, const mjtNum * vec2, int n) { return mju_mulVecMatVec            (vec1, mat, vec2, n  ); }
  void   _transpose          (mjtNum * res, const mjtNum * mat, int nr, int nc) { return mju_transpose               (res, mat, nr, nc    ); }
  void   _symmetrize         (mjtNum * res, const mjtNum * mat, int n) { return mju_symmetrize              (res, mat, n         ); }
  void   _eye                (mjtNum * mat, int n ) { return mju_eye                     (mat, n              ); }
  void   _mulMatMat          (mjtNum * res, const mjtNum * mat1, const mjtNum * mat2, int r1, int c1, int c2) { return mju_mulMatMat               (res, mat1, mat2, r1, c1, c2); }
  void   _mulMatMatT         (mjtNum * res, const mjtNum * mat1, const mjtNum * mat2, int r1, int c1, int r2) { return mju_mulMatMatT              (res, mat1, mat2, r1, c1, r2); }
  void   _mulMatTMat         (mjtNum * res, const mjtNum * mat1, const mjtNum * mat2, int r1, int c1, int c2) { return mju_mulMatTMat              (res, mat1, mat2, r1, c1, c2); }
  void   _sqrMatTD           (mjtNum * res, const mjtNum * mat, const mjtNum * diag, int nr, int nc) { return mju_sqrMatTD                (res, mat, diag, nr, nc); }
  int    _cholFactor         (mjtNum * mat, int n, mjtNum mindiag) { return mju_cholFactor              (mat, n, mindiag     ); }
  void   _cholSolve          (mjtNum * res, const mjtNum * mat, const mjtNum * vec, int n) { return mju_cholSolve               (res, mat, vec, n    ); }
  int    _cholUpdate         (mjtNum * mat, mjtNum * x, int n, int flg_plus) { return mju_cholUpdate              (mat, x, n, flg_plus ); }
  void   _encodePyramid      (mjtNum * pyramid, const mjtNum * force, const mjtNum * mu, int dim) { return mju_encodePyramid           (pyramid, force, mu, dim); }
  void   _decodePyramid      (mjtNum * force, const mjtNum * pyramid, const mjtNum * mu, int dim) { return mju_decodePyramid           (force, pyramid, mu, dim); }
  mjtNum _springDamper       (mjtNum pos0, mjtNum vel0, mjtNum Kp, mjtNum Kv, mjtNum dt) { return mju_springDamper            (pos0, vel0, Kp, Kv, dt); }
  mjtNum _min                (mjtNum a, mjtNum b  ) { return mju_min                     (a, b                ); }
  mjtNum _max                (mjtNum a, mjtNum b  ) { return mju_max                     (a, b                ); }
  mjtNum _clip               (mjtNum x, mjtNum min, mjtNum max) { return mju_clip                    (x, min, max         ); }
  mjtNum _sign               (mjtNum x            ) { return mju_sign                    (x                   ); }
  int    _round              (mjtNum x            ) { return mju_round                   (x                   ); }
  std::string _type2Str           (int type            ) { return std::string(mju_type2Str                (type                )); }
  int    _str2Type           (std::string str     ) { return mju_str2Type                (str.c_str()         ); }
  std::string _writeNumBytes      (size_t nbytes       ) { return std::string(mju_writeNumBytes           (nbytes              )); }
  std::string _warningText        (int warning, size_t info) { return std::string(mju_warningText             (warning, info       )); }
  int    _isBad              (mjtNum x            ) { return mju_isBad                   (x                   ); }
  int    _isZero             (mjtNum * vec, int n ) { return mju_isZero                  (vec, n              ); }
  mjtNum _standardNormal     (mjtNum * num2       ) { return mju_standardNormal          (num2                ); }
  void   _insertionSort      (mjtNum * list, int n) { return mju_insertionSort           (list, n             ); }
  mjtNum _Halton             (int index, int base ) { return mju_Halton                  (index, base         ); }
  mjtNum _sigmoid            (mjtNum x            ) { return mju_sigmoid                 (x                   ); }
  void   _transitionFD       (mjtNum eps, mjtByte centered, mjtNum * A, mjtNum * B, mjtNum * C, mjtNum * D) { return mjd_transitionFD            (_model->ptr(), _state->ptr(), eps, centered, A, B, C, D); }
  int    _pluginCount        (                    ) { return mjp_pluginCount             (                    ); }


private:
  Model *_model;
  State *_state;
};

// main function
int main(int argc, char **argv) {
  std::printf("MuJoCo version: %d\n\n", mj_version());
  return 0;
}

EMSCRIPTEN_BINDINGS(mujoco_wasm) {

  // MODEL_ENUMS
  enum_<mjtDisableBit>("mjtDisableBit")
      .value("mjDSBL_CONSTRAINT"      , mjtDisableBit            ::mjDSBL_CONSTRAINT        )
      .value("mjDSBL_EQUALITY"        , mjtDisableBit            ::mjDSBL_EQUALITY          )
      .value("mjDSBL_FRICTIONLOSS"    , mjtDisableBit            ::mjDSBL_FRICTIONLOSS      )
      .value("mjDSBL_LIMIT"           , mjtDisableBit            ::mjDSBL_LIMIT             )
      .value("mjDSBL_CONTACT"         , mjtDisableBit            ::mjDSBL_CONTACT           )
      .value("mjDSBL_PASSIVE"         , mjtDisableBit            ::mjDSBL_PASSIVE           )
      .value("mjDSBL_GRAVITY"         , mjtDisableBit            ::mjDSBL_GRAVITY           )
      .value("mjDSBL_CLAMPCTRL"       , mjtDisableBit            ::mjDSBL_CLAMPCTRL         )
      .value("mjDSBL_WARMSTART"       , mjtDisableBit            ::mjDSBL_WARMSTART         )
      .value("mjDSBL_FILTERPARENT"    , mjtDisableBit            ::mjDSBL_FILTERPARENT      )
      .value("mjDSBL_ACTUATION"       , mjtDisableBit            ::mjDSBL_ACTUATION         )
      .value("mjDSBL_REFSAFE"         , mjtDisableBit            ::mjDSBL_REFSAFE           )
      .value("mjDSBL_SENSOR"          , mjtDisableBit            ::mjDSBL_SENSOR            )
      .value("mjNDISABLE"             , mjtDisableBit            ::mjNDISABLE               )
  ;
  enum_<mjtEnableBit>("mjtEnableBit")
      .value("mjENBL_OVERRIDE"        , mjtEnableBit             ::mjENBL_OVERRIDE          )
      .value("mjENBL_ENERGY"          , mjtEnableBit             ::mjENBL_ENERGY            )
      .value("mjENBL_FWDINV"          , mjtEnableBit             ::mjENBL_FWDINV            )
      .value("mjENBL_SENSORNOISE"     , mjtEnableBit             ::mjENBL_SENSORNOISE       )
      .value("mjENBL_MULTICCD"        , mjtEnableBit             ::mjENBL_MULTICCD          )
      .value("mjNENABLE"              , mjtEnableBit             ::mjNENABLE                )
  ;
  enum_<mjtJoint>("mjtJoint")
      .value("mjJNT_FREE"             , mjtJoint                 ::mjJNT_FREE               )
      .value("mjJNT_BALL"             , mjtJoint                 ::mjJNT_BALL               )
      .value("mjJNT_SLIDE"            , mjtJoint                 ::mjJNT_SLIDE              )
      .value("mjJNT_HINGE"            , mjtJoint                 ::mjJNT_HINGE              )
  ;
  enum_<mjtGeom>("mjtGeom")
      .value("mjGEOM_PLANE"           , mjtGeom                  ::mjGEOM_PLANE             )
      .value("mjGEOM_HFIELD"          , mjtGeom                  ::mjGEOM_HFIELD            )
      .value("mjGEOM_SPHERE"          , mjtGeom                  ::mjGEOM_SPHERE            )
      .value("mjGEOM_CAPSULE"         , mjtGeom                  ::mjGEOM_CAPSULE           )
      .value("mjGEOM_ELLIPSOID"       , mjtGeom                  ::mjGEOM_ELLIPSOID         )
      .value("mjGEOM_CYLINDER"        , mjtGeom                  ::mjGEOM_CYLINDER          )
      .value("mjGEOM_BOX"             , mjtGeom                  ::mjGEOM_BOX               )
      .value("mjGEOM_MESH"            , mjtGeom                  ::mjGEOM_MESH              )
      .value("mjNGEOMTYPES"           , mjtGeom                  ::mjNGEOMTYPES             )
      .value("mjGEOM_ARROW"           , mjtGeom                  ::mjGEOM_ARROW             )
      .value("mjGEOM_ARROW1"          , mjtGeom                  ::mjGEOM_ARROW1            )
      .value("mjGEOM_ARROW2"          , mjtGeom                  ::mjGEOM_ARROW2            )
      .value("mjGEOM_LINE"            , mjtGeom                  ::mjGEOM_LINE              )
      .value("mjGEOM_SKIN"            , mjtGeom                  ::mjGEOM_SKIN              )
      .value("mjGEOM_LABEL"           , mjtGeom                  ::mjGEOM_LABEL             )
      .value("mjGEOM_NONE"            , mjtGeom                  ::mjGEOM_NONE              )
  ;
  enum_<mjtCamLight>("mjtCamLight")
      .value("mjCAMLIGHT_FIXED"       , mjtCamLight              ::mjCAMLIGHT_FIXED         )
      .value("mjCAMLIGHT_TRACK"       , mjtCamLight              ::mjCAMLIGHT_TRACK         )
      .value("mjCAMLIGHT_TRACKCOM"    , mjtCamLight              ::mjCAMLIGHT_TRACKCOM      )
      .value("mjCAMLIGHT_TARGETBODY"  , mjtCamLight              ::mjCAMLIGHT_TARGETBODY    )
      .value("mjCAMLIGHT_TARGETBODYCOM", mjtCamLight              ::mjCAMLIGHT_TARGETBODYCOM )
  ;
  enum_<mjtTexture>("mjtTexture")
      .value("mjTEXTURE_2D"           , mjtTexture               ::mjTEXTURE_2D             )
      .value("mjTEXTURE_CUBE"         , mjtTexture               ::mjTEXTURE_CUBE           )
      .value("mjTEXTURE_SKYBOX"       , mjtTexture               ::mjTEXTURE_SKYBOX         )
  ;
  enum_<mjtIntegrator>("mjtIntegrator")
      .value("mjINT_EULER"            , mjtIntegrator            ::mjINT_EULER              )
      .value("mjINT_RK4"              , mjtIntegrator            ::mjINT_RK4                )
      .value("mjINT_IMPLICIT"         , mjtIntegrator            ::mjINT_IMPLICIT           )
  ;
  enum_<mjtCollision>("mjtCollision")
      .value("mjCOL_ALL"              , mjtCollision             ::mjCOL_ALL                )
      .value("mjCOL_PAIR"             , mjtCollision             ::mjCOL_PAIR               )
      .value("mjCOL_DYNAMIC"          , mjtCollision             ::mjCOL_DYNAMIC            )
  ;
  enum_<mjtCone>("mjtCone")
      .value("mjCONE_PYRAMIDAL"       , mjtCone                  ::mjCONE_PYRAMIDAL         )
      .value("mjCONE_ELLIPTIC"        , mjtCone                  ::mjCONE_ELLIPTIC          )
  ;
  enum_<mjtJacobian>("mjtJacobian")
      .value("mjJAC_DENSE"            , mjtJacobian              ::mjJAC_DENSE              )
      .value("mjJAC_SPARSE"           , mjtJacobian              ::mjJAC_SPARSE             )
      .value("mjJAC_AUTO"             , mjtJacobian              ::mjJAC_AUTO               )
  ;
  enum_<mjtSolver>("mjtSolver")
      .value("mjSOL_PGS"              , mjtSolver                ::mjSOL_PGS                )
      .value("mjSOL_CG"               , mjtSolver                ::mjSOL_CG                 )
      .value("mjSOL_NEWTON"           , mjtSolver                ::mjSOL_NEWTON             )
  ;
  enum_<mjtEq>("mjtEq")
      .value("mjEQ_CONNECT"           , mjtEq                    ::mjEQ_CONNECT             )
      .value("mjEQ_WELD"              , mjtEq                    ::mjEQ_WELD                )
      .value("mjEQ_JOINT"             , mjtEq                    ::mjEQ_JOINT               )
      .value("mjEQ_TENDON"            , mjtEq                    ::mjEQ_TENDON              )
      .value("mjEQ_DISTANCE"          , mjtEq                    ::mjEQ_DISTANCE            )
  ;
  enum_<mjtWrap>("mjtWrap")
      .value("mjWRAP_NONE"            , mjtWrap                  ::mjWRAP_NONE              )
      .value("mjWRAP_JOINT"           , mjtWrap                  ::mjWRAP_JOINT             )
      .value("mjWRAP_PULLEY"          , mjtWrap                  ::mjWRAP_PULLEY            )
      .value("mjWRAP_SITE"            , mjtWrap                  ::mjWRAP_SITE              )
      .value("mjWRAP_SPHERE"          , mjtWrap                  ::mjWRAP_SPHERE            )
      .value("mjWRAP_CYLINDER"        , mjtWrap                  ::mjWRAP_CYLINDER          )
  ;
  enum_<mjtTrn>("mjtTrn")
      .value("mjTRN_JOINT"            , mjtTrn                   ::mjTRN_JOINT              )
      .value("mjTRN_JOINTINPARENT"    , mjtTrn                   ::mjTRN_JOINTINPARENT      )
      .value("mjTRN_SLIDERCRANK"      , mjtTrn                   ::mjTRN_SLIDERCRANK        )
      .value("mjTRN_TENDON"           , mjtTrn                   ::mjTRN_TENDON             )
      .value("mjTRN_SITE"             , mjtTrn                   ::mjTRN_SITE               )
      .value("mjTRN_BODY"             , mjtTrn                   ::mjTRN_BODY               )
      .value("mjTRN_UNDEFINED"        , mjtTrn                   ::mjTRN_UNDEFINED          )
  ;
  enum_<mjtDyn>("mjtDyn")
      .value("mjDYN_NONE"             , mjtDyn                   ::mjDYN_NONE               )
      .value("mjDYN_INTEGRATOR"       , mjtDyn                   ::mjDYN_INTEGRATOR         )
      .value("mjDYN_FILTER"           , mjtDyn                   ::mjDYN_FILTER             )
      .value("mjDYN_MUSCLE"           , mjtDyn                   ::mjDYN_MUSCLE             )
      .value("mjDYN_USER"             , mjtDyn                   ::mjDYN_USER               )
  ;
  enum_<mjtGain>("mjtGain")
      .value("mjGAIN_FIXED"           , mjtGain                  ::mjGAIN_FIXED             )
      .value("mjGAIN_AFFINE"          , mjtGain                  ::mjGAIN_AFFINE            )
      .value("mjGAIN_MUSCLE"          , mjtGain                  ::mjGAIN_MUSCLE            )
      .value("mjGAIN_USER"            , mjtGain                  ::mjGAIN_USER              )
  ;
  enum_<mjtBias>("mjtBias")
      .value("mjBIAS_NONE"            , mjtBias                  ::mjBIAS_NONE              )
      .value("mjBIAS_AFFINE"          , mjtBias                  ::mjBIAS_AFFINE            )
      .value("mjBIAS_MUSCLE"          , mjtBias                  ::mjBIAS_MUSCLE            )
      .value("mjBIAS_USER"            , mjtBias                  ::mjBIAS_USER              )
  ;
  enum_<mjtObj>("mjtObj")
      .value("mjOBJ_UNKNOWN"          , mjtObj                   ::mjOBJ_UNKNOWN            )
      .value("mjOBJ_BODY"             , mjtObj                   ::mjOBJ_BODY               )
      .value("mjOBJ_XBODY"            , mjtObj                   ::mjOBJ_XBODY              )
      .value("mjOBJ_JOINT"            , mjtObj                   ::mjOBJ_JOINT              )
      .value("mjOBJ_DOF"              , mjtObj                   ::mjOBJ_DOF                )
      .value("mjOBJ_GEOM"             , mjtObj                   ::mjOBJ_GEOM               )
      .value("mjOBJ_SITE"             , mjtObj                   ::mjOBJ_SITE               )
      .value("mjOBJ_CAMERA"           , mjtObj                   ::mjOBJ_CAMERA             )
      .value("mjOBJ_LIGHT"            , mjtObj                   ::mjOBJ_LIGHT              )
      .value("mjOBJ_MESH"             , mjtObj                   ::mjOBJ_MESH               )
      .value("mjOBJ_SKIN"             , mjtObj                   ::mjOBJ_SKIN               )
      .value("mjOBJ_HFIELD"           , mjtObj                   ::mjOBJ_HFIELD             )
      .value("mjOBJ_TEXTURE"          , mjtObj                   ::mjOBJ_TEXTURE            )
      .value("mjOBJ_MATERIAL"         , mjtObj                   ::mjOBJ_MATERIAL           )
      .value("mjOBJ_PAIR"             , mjtObj                   ::mjOBJ_PAIR               )
      .value("mjOBJ_EXCLUDE"          , mjtObj                   ::mjOBJ_EXCLUDE            )
      .value("mjOBJ_EQUALITY"         , mjtObj                   ::mjOBJ_EQUALITY           )
      .value("mjOBJ_TENDON"           , mjtObj                   ::mjOBJ_TENDON             )
      .value("mjOBJ_ACTUATOR"         , mjtObj                   ::mjOBJ_ACTUATOR           )
      .value("mjOBJ_SENSOR"           , mjtObj                   ::mjOBJ_SENSOR             )
      .value("mjOBJ_NUMERIC"          , mjtObj                   ::mjOBJ_NUMERIC            )
      .value("mjOBJ_TEXT"             , mjtObj                   ::mjOBJ_TEXT               )
      .value("mjOBJ_TUPLE"            , mjtObj                   ::mjOBJ_TUPLE              )
      .value("mjOBJ_KEY"              , mjtObj                   ::mjOBJ_KEY                )
      .value("mjOBJ_PLUGIN"           , mjtObj                   ::mjOBJ_PLUGIN             )
  ;
  enum_<mjtConstraint>("mjtConstraint")
      .value("mjCNSTR_EQUALITY"       , mjtConstraint            ::mjCNSTR_EQUALITY         )
      .value("mjCNSTR_FRICTION_DOF"   , mjtConstraint            ::mjCNSTR_FRICTION_DOF     )
      .value("mjCNSTR_FRICTION_TENDON", mjtConstraint            ::mjCNSTR_FRICTION_TENDON  )
      .value("mjCNSTR_LIMIT_JOINT"    , mjtConstraint            ::mjCNSTR_LIMIT_JOINT      )
      .value("mjCNSTR_LIMIT_TENDON"   , mjtConstraint            ::mjCNSTR_LIMIT_TENDON     )
      .value("mjCNSTR_CONTACT_FRICTIONLESS", mjtConstraint            ::mjCNSTR_CONTACT_FRICTIONLESS)
      .value("mjCNSTR_CONTACT_PYRAMIDAL", mjtConstraint            ::mjCNSTR_CONTACT_PYRAMIDAL)
      .value("mjCNSTR_CONTACT_ELLIPTIC", mjtConstraint            ::mjCNSTR_CONTACT_ELLIPTIC )
  ;
  enum_<mjtConstraintState>("mjtConstraintState")
      .value("mjCNSTRSTATE_SATISFIED" , mjtConstraintState       ::mjCNSTRSTATE_SATISFIED   )
      .value("mjCNSTRSTATE_QUADRATIC" , mjtConstraintState       ::mjCNSTRSTATE_QUADRATIC   )
      .value("mjCNSTRSTATE_LINEARNEG" , mjtConstraintState       ::mjCNSTRSTATE_LINEARNEG   )
      .value("mjCNSTRSTATE_LINEARPOS" , mjtConstraintState       ::mjCNSTRSTATE_LINEARPOS   )
      .value("mjCNSTRSTATE_CONE"      , mjtConstraintState       ::mjCNSTRSTATE_CONE        )
  ;
  enum_<mjtSensor>("mjtSensor")
      .value("mjSENS_TOUCH"           , mjtSensor                ::mjSENS_TOUCH             )
      .value("mjSENS_ACCELEROMETER"   , mjtSensor                ::mjSENS_ACCELEROMETER     )
      .value("mjSENS_VELOCIMETER"     , mjtSensor                ::mjSENS_VELOCIMETER       )
      .value("mjSENS_GYRO"            , mjtSensor                ::mjSENS_GYRO              )
      .value("mjSENS_FORCE"           , mjtSensor                ::mjSENS_FORCE             )
      .value("mjSENS_TORQUE"          , mjtSensor                ::mjSENS_TORQUE            )
      .value("mjSENS_MAGNETOMETER"    , mjtSensor                ::mjSENS_MAGNETOMETER      )
      .value("mjSENS_RANGEFINDER"     , mjtSensor                ::mjSENS_RANGEFINDER       )
      .value("mjSENS_JOINTPOS"        , mjtSensor                ::mjSENS_JOINTPOS          )
      .value("mjSENS_JOINTVEL"        , mjtSensor                ::mjSENS_JOINTVEL          )
      .value("mjSENS_TENDONPOS"       , mjtSensor                ::mjSENS_TENDONPOS         )
      .value("mjSENS_TENDONVEL"       , mjtSensor                ::mjSENS_TENDONVEL         )
      .value("mjSENS_ACTUATORPOS"     , mjtSensor                ::mjSENS_ACTUATORPOS       )
      .value("mjSENS_ACTUATORVEL"     , mjtSensor                ::mjSENS_ACTUATORVEL       )
      .value("mjSENS_ACTUATORFRC"     , mjtSensor                ::mjSENS_ACTUATORFRC       )
      .value("mjSENS_BALLQUAT"        , mjtSensor                ::mjSENS_BALLQUAT          )
      .value("mjSENS_BALLANGVEL"      , mjtSensor                ::mjSENS_BALLANGVEL        )
      .value("mjSENS_JOINTLIMITPOS"   , mjtSensor                ::mjSENS_JOINTLIMITPOS     )
      .value("mjSENS_JOINTLIMITVEL"   , mjtSensor                ::mjSENS_JOINTLIMITVEL     )
      .value("mjSENS_JOINTLIMITFRC"   , mjtSensor                ::mjSENS_JOINTLIMITFRC     )
      .value("mjSENS_TENDONLIMITPOS"  , mjtSensor                ::mjSENS_TENDONLIMITPOS    )
      .value("mjSENS_TENDONLIMITVEL"  , mjtSensor                ::mjSENS_TENDONLIMITVEL    )
      .value("mjSENS_TENDONLIMITFRC"  , mjtSensor                ::mjSENS_TENDONLIMITFRC    )
      .value("mjSENS_FRAMEPOS"        , mjtSensor                ::mjSENS_FRAMEPOS          )
      .value("mjSENS_FRAMEQUAT"       , mjtSensor                ::mjSENS_FRAMEQUAT         )
      .value("mjSENS_FRAMEXAXIS"      , mjtSensor                ::mjSENS_FRAMEXAXIS        )
      .value("mjSENS_FRAMEYAXIS"      , mjtSensor                ::mjSENS_FRAMEYAXIS        )
      .value("mjSENS_FRAMEZAXIS"      , mjtSensor                ::mjSENS_FRAMEZAXIS        )
      .value("mjSENS_FRAMELINVEL"     , mjtSensor                ::mjSENS_FRAMELINVEL       )
      .value("mjSENS_FRAMEANGVEL"     , mjtSensor                ::mjSENS_FRAMEANGVEL       )
      .value("mjSENS_FRAMELINACC"     , mjtSensor                ::mjSENS_FRAMELINACC       )
      .value("mjSENS_FRAMEANGACC"     , mjtSensor                ::mjSENS_FRAMEANGACC       )
      .value("mjSENS_SUBTREECOM"      , mjtSensor                ::mjSENS_SUBTREECOM        )
      .value("mjSENS_SUBTREELINVEL"   , mjtSensor                ::mjSENS_SUBTREELINVEL     )
      .value("mjSENS_SUBTREEANGMOM"   , mjtSensor                ::mjSENS_SUBTREEANGMOM     )
      .value("mjSENS_CLOCK"           , mjtSensor                ::mjSENS_CLOCK             )
      .value("mjSENS_PLUGIN"          , mjtSensor                ::mjSENS_PLUGIN            )
      .value("mjSENS_USER"            , mjtSensor                ::mjSENS_USER              )
  ;
  enum_<mjtStage>("mjtStage")
      .value("mjSTAGE_NONE"           , mjtStage                 ::mjSTAGE_NONE             )
      .value("mjSTAGE_POS"            , mjtStage                 ::mjSTAGE_POS              )
      .value("mjSTAGE_VEL"            , mjtStage                 ::mjSTAGE_VEL              )
      .value("mjSTAGE_ACC"            , mjtStage                 ::mjSTAGE_ACC              )
  ;
  enum_<mjtDataType>("mjtDataType")
      .value("mjDATATYPE_REAL"        , mjtDataType              ::mjDATATYPE_REAL          )
      .value("mjDATATYPE_POSITIVE"    , mjtDataType              ::mjDATATYPE_POSITIVE      )
      .value("mjDATATYPE_AXIS"        , mjtDataType              ::mjDATATYPE_AXIS          )
      .value("mjDATATYPE_QUATERNION"  , mjtDataType              ::mjDATATYPE_QUATERNION    )
  ;
  enum_<mjtLRMode>("mjtLRMode")
      .value("mjLRMODE_NONE"          , mjtLRMode                ::mjLRMODE_NONE            )
      .value("mjLRMODE_MUSCLE"        , mjtLRMode                ::mjLRMODE_MUSCLE          )
      .value("mjLRMODE_MUSCLEUSER"    , mjtLRMode                ::mjLRMODE_MUSCLEUSER      )
      .value("mjLRMODE_ALL"           , mjtLRMode                ::mjLRMODE_ALL             )
  ;


  class_<Model>("Model")
      .constructor<>(&Model::load_from_xml)
      .class_function("load_from_xml", &Model::load_from_xml)
      .function("ptr", &Model::ptr, allow_raw_pointers())
      .function("getVal"          , &Model::getVal      )
      .function("getOptions"      , &Model::getOptions  )
      // MJMODEL_BINDINGS
      .function("nq"                    , &Model::nq                    )
      .function("nv"                    , &Model::nv                    )
      .function("nu"                    , &Model::nu                    )
      .function("na"                    , &Model::na                    )
      .function("nbody"                 , &Model::nbody                 )
      .function("njnt"                  , &Model::njnt                  )
      .function("ngeom"                 , &Model::ngeom                 )
      .function("nsite"                 , &Model::nsite                 )
      .function("ncam"                  , &Model::ncam                  )
      .function("nlight"                , &Model::nlight                )
      .function("nmesh"                 , &Model::nmesh                 )
      .function("nmeshvert"             , &Model::nmeshvert             )
      .function("nmeshtexvert"          , &Model::nmeshtexvert          )
      .function("nmeshface"             , &Model::nmeshface             )
      .function("nmeshgraph"            , &Model::nmeshgraph            )
      .function("nskin"                 , &Model::nskin                 )
      .function("nskinvert"             , &Model::nskinvert             )
      .function("nskintexvert"          , &Model::nskintexvert          )
      .function("nskinface"             , &Model::nskinface             )
      .function("nskinbone"             , &Model::nskinbone             )
      .function("nskinbonevert"         , &Model::nskinbonevert         )
      .function("nhfield"               , &Model::nhfield               )
      .function("nhfielddata"           , &Model::nhfielddata           )
      .function("ntex"                  , &Model::ntex                  )
      .function("ntexdata"              , &Model::ntexdata              )
      .function("nmat"                  , &Model::nmat                  )
      .function("npair"                 , &Model::npair                 )
      .function("nexclude"              , &Model::nexclude              )
      .function("neq"                   , &Model::neq                   )
      .function("ntendon"               , &Model::ntendon               )
      .function("nwrap"                 , &Model::nwrap                 )
      .function("nsensor"               , &Model::nsensor               )
      .function("nnumeric"              , &Model::nnumeric              )
      .function("nnumericdata"          , &Model::nnumericdata          )
      .function("ntext"                 , &Model::ntext                 )
      .function("ntextdata"             , &Model::ntextdata             )
      .function("ntuple"                , &Model::ntuple                )
      .function("ntupledata"            , &Model::ntupledata            )
      .function("nkey"                  , &Model::nkey                  )
      .function("nmocap"                , &Model::nmocap                )
      .function("nplugin"               , &Model::nplugin               )
      .function("npluginattr"           , &Model::npluginattr           )
      .function("nuser_body"            , &Model::nuser_body            )
      .function("nuser_jnt"             , &Model::nuser_jnt             )
      .function("nuser_geom"            , &Model::nuser_geom            )
      .function("nuser_site"            , &Model::nuser_site            )
      .function("nuser_cam"             , &Model::nuser_cam             )
      .function("nuser_tendon"          , &Model::nuser_tendon          )
      .function("nuser_actuator"        , &Model::nuser_actuator        )
      .function("nuser_sensor"          , &Model::nuser_sensor          )
      .function("nnames"                , &Model::nnames                )
      .function("nM"                    , &Model::nM                    )
      .function("nD"                    , &Model::nD                    )
      .function("nemax"                 , &Model::nemax                 )
      .function("njmax"                 , &Model::njmax                 )
      .function("nconmax"               , &Model::nconmax               )
      .function("nstack"                , &Model::nstack                )
      .function("nuserdata"             , &Model::nuserdata             )
      .function("nsensordata"           , &Model::nsensordata           )
      .function("npluginstate"          , &Model::npluginstate          )
      .function("nbuffer"               , &Model::nbuffer               )
      .function("qpos0"                 , &Model::qpos0                 )
      .function("qpos_spring"           , &Model::qpos_spring           )
      .function("body_parentid"         , &Model::body_parentid         )
      .function("body_rootid"           , &Model::body_rootid           )
      .function("body_weldid"           , &Model::body_weldid           )
      .function("body_mocapid"          , &Model::body_mocapid          )
      .function("body_jntnum"           , &Model::body_jntnum           )
      .function("body_jntadr"           , &Model::body_jntadr           )
      .function("body_dofnum"           , &Model::body_dofnum           )
      .function("body_dofadr"           , &Model::body_dofadr           )
      .function("body_geomnum"          , &Model::body_geomnum          )
      .function("body_geomadr"          , &Model::body_geomadr          )
      .function("body_simple"           , &Model::body_simple           )
      .function("body_sameframe"        , &Model::body_sameframe        )
      .function("body_pos"              , &Model::body_pos              )
      .function("body_quat"             , &Model::body_quat             )
      .function("body_ipos"             , &Model::body_ipos             )
      .function("body_iquat"            , &Model::body_iquat            )
      .function("body_mass"             , &Model::body_mass             )
      .function("body_subtreemass"      , &Model::body_subtreemass      )
      .function("body_inertia"          , &Model::body_inertia          )
      .function("body_invweight0"       , &Model::body_invweight0       )
      .function("body_gravcomp"         , &Model::body_gravcomp         )
      .function("body_user"             , &Model::body_user             )
      .function("body_plugin"           , &Model::body_plugin           )
      .function("jnt_type"              , &Model::jnt_type              )
      .function("jnt_qposadr"           , &Model::jnt_qposadr           )
      .function("jnt_dofadr"            , &Model::jnt_dofadr            )
      .function("jnt_bodyid"            , &Model::jnt_bodyid            )
      .function("jnt_group"             , &Model::jnt_group             )
      .function("jnt_limited"           , &Model::jnt_limited           )
      .function("jnt_solref"            , &Model::jnt_solref            )
      .function("jnt_solimp"            , &Model::jnt_solimp            )
      .function("jnt_pos"               , &Model::jnt_pos               )
      .function("jnt_axis"              , &Model::jnt_axis              )
      .function("jnt_stiffness"         , &Model::jnt_stiffness         )
      .function("jnt_range"             , &Model::jnt_range             )
      .function("jnt_margin"            , &Model::jnt_margin            )
      .function("jnt_user"              , &Model::jnt_user              )
      .function("dof_bodyid"            , &Model::dof_bodyid            )
      .function("dof_jntid"             , &Model::dof_jntid             )
      .function("dof_parentid"          , &Model::dof_parentid          )
      .function("dof_Madr"              , &Model::dof_Madr              )
      .function("dof_simplenum"         , &Model::dof_simplenum         )
      .function("dof_solref"            , &Model::dof_solref            )
      .function("dof_solimp"            , &Model::dof_solimp            )
      .function("dof_frictionloss"      , &Model::dof_frictionloss      )
      .function("dof_armature"          , &Model::dof_armature          )
      .function("dof_damping"           , &Model::dof_damping           )
      .function("dof_invweight0"        , &Model::dof_invweight0        )
      .function("dof_M0"                , &Model::dof_M0                )
      .function("geom_type"             , &Model::geom_type             )
      .function("geom_contype"          , &Model::geom_contype          )
      .function("geom_conaffinity"      , &Model::geom_conaffinity      )
      .function("geom_condim"           , &Model::geom_condim           )
      .function("geom_bodyid"           , &Model::geom_bodyid           )
      .function("geom_dataid"           , &Model::geom_dataid           )
      .function("geom_matid"            , &Model::geom_matid            )
      .function("geom_group"            , &Model::geom_group            )
      .function("geom_priority"         , &Model::geom_priority         )
      .function("geom_sameframe"        , &Model::geom_sameframe        )
      .function("geom_solmix"           , &Model::geom_solmix           )
      .function("geom_solref"           , &Model::geom_solref           )
      .function("geom_solimp"           , &Model::geom_solimp           )
      .function("geom_size"             , &Model::geom_size             )
      .function("geom_rbound"           , &Model::geom_rbound           )
      .function("geom_pos"              , &Model::geom_pos              )
      .function("geom_quat"             , &Model::geom_quat             )
      .function("geom_friction"         , &Model::geom_friction         )
      .function("geom_margin"           , &Model::geom_margin           )
      .function("geom_gap"              , &Model::geom_gap              )
      .function("geom_fluid"            , &Model::geom_fluid            )
      .function("geom_user"             , &Model::geom_user             )
      .function("geom_rgba"             , &Model::geom_rgba             )
      .function("site_type"             , &Model::site_type             )
      .function("site_bodyid"           , &Model::site_bodyid           )
      .function("site_matid"            , &Model::site_matid            )
      .function("site_group"            , &Model::site_group            )
      .function("site_sameframe"        , &Model::site_sameframe        )
      .function("site_size"             , &Model::site_size             )
      .function("site_pos"              , &Model::site_pos              )
      .function("site_quat"             , &Model::site_quat             )
      .function("site_user"             , &Model::site_user             )
      .function("site_rgba"             , &Model::site_rgba             )
      .function("cam_mode"              , &Model::cam_mode              )
      .function("cam_bodyid"            , &Model::cam_bodyid            )
      .function("cam_targetbodyid"      , &Model::cam_targetbodyid      )
      .function("cam_pos"               , &Model::cam_pos               )
      .function("cam_quat"              , &Model::cam_quat              )
      .function("cam_poscom0"           , &Model::cam_poscom0           )
      .function("cam_pos0"              , &Model::cam_pos0              )
      .function("cam_mat0"              , &Model::cam_mat0              )
      .function("cam_fovy"              , &Model::cam_fovy              )
      .function("cam_ipd"               , &Model::cam_ipd               )
      .function("cam_user"              , &Model::cam_user              )
      .function("light_mode"            , &Model::light_mode            )
      .function("light_bodyid"          , &Model::light_bodyid          )
      .function("light_targetbodyid"    , &Model::light_targetbodyid    )
      .function("light_directional"     , &Model::light_directional     )
      .function("light_castshadow"      , &Model::light_castshadow      )
      .function("light_active"          , &Model::light_active          )
      .function("light_pos"             , &Model::light_pos             )
      .function("light_dir"             , &Model::light_dir             )
      .function("light_poscom0"         , &Model::light_poscom0         )
      .function("light_pos0"            , &Model::light_pos0            )
      .function("light_dir0"            , &Model::light_dir0            )
      .function("light_attenuation"     , &Model::light_attenuation     )
      .function("light_cutoff"          , &Model::light_cutoff          )
      .function("light_exponent"        , &Model::light_exponent        )
      .function("light_ambient"         , &Model::light_ambient         )
      .function("light_diffuse"         , &Model::light_diffuse         )
      .function("light_specular"        , &Model::light_specular        )
      .function("mesh_vertadr"          , &Model::mesh_vertadr          )
      .function("mesh_vertnum"          , &Model::mesh_vertnum          )
      .function("mesh_texcoordadr"      , &Model::mesh_texcoordadr      )
      .function("mesh_faceadr"          , &Model::mesh_faceadr          )
      .function("mesh_facenum"          , &Model::mesh_facenum          )
      .function("mesh_graphadr"         , &Model::mesh_graphadr         )
      .function("mesh_vert"             , &Model::mesh_vert             )
      .function("mesh_normal"           , &Model::mesh_normal           )
      .function("mesh_texcoord"         , &Model::mesh_texcoord         )
      .function("mesh_face"             , &Model::mesh_face             )
      .function("mesh_graph"            , &Model::mesh_graph            )
      .function("skin_matid"            , &Model::skin_matid            )
      .function("skin_group"            , &Model::skin_group            )
      .function("skin_rgba"             , &Model::skin_rgba             )
      .function("skin_inflate"          , &Model::skin_inflate          )
      .function("skin_vertadr"          , &Model::skin_vertadr          )
      .function("skin_vertnum"          , &Model::skin_vertnum          )
      .function("skin_texcoordadr"      , &Model::skin_texcoordadr      )
      .function("skin_faceadr"          , &Model::skin_faceadr          )
      .function("skin_facenum"          , &Model::skin_facenum          )
      .function("skin_boneadr"          , &Model::skin_boneadr          )
      .function("skin_bonenum"          , &Model::skin_bonenum          )
      .function("skin_vert"             , &Model::skin_vert             )
      .function("skin_texcoord"         , &Model::skin_texcoord         )
      .function("skin_face"             , &Model::skin_face             )
      .function("skin_bonevertadr"      , &Model::skin_bonevertadr      )
      .function("skin_bonevertnum"      , &Model::skin_bonevertnum      )
      .function("skin_bonebindpos"      , &Model::skin_bonebindpos      )
      .function("skin_bonebindquat"     , &Model::skin_bonebindquat     )
      .function("skin_bonebodyid"       , &Model::skin_bonebodyid       )
      .function("skin_bonevertid"       , &Model::skin_bonevertid       )
      .function("skin_bonevertweight"   , &Model::skin_bonevertweight   )
      .function("hfield_size"           , &Model::hfield_size           )
      .function("hfield_nrow"           , &Model::hfield_nrow           )
      .function("hfield_ncol"           , &Model::hfield_ncol           )
      .function("hfield_adr"            , &Model::hfield_adr            )
      .function("hfield_data"           , &Model::hfield_data           )
      .function("tex_type"              , &Model::tex_type              )
      .function("tex_height"            , &Model::tex_height            )
      .function("tex_width"             , &Model::tex_width             )
      .function("tex_adr"               , &Model::tex_adr               )
      .function("tex_rgb"               , &Model::tex_rgb               )
      .function("mat_texid"             , &Model::mat_texid             )
      .function("mat_texuniform"        , &Model::mat_texuniform        )
      .function("mat_texrepeat"         , &Model::mat_texrepeat         )
      .function("mat_emission"          , &Model::mat_emission          )
      .function("mat_specular"          , &Model::mat_specular          )
      .function("mat_shininess"         , &Model::mat_shininess         )
      .function("mat_reflectance"       , &Model::mat_reflectance       )
      .function("mat_rgba"              , &Model::mat_rgba              )
      .function("pair_dim"              , &Model::pair_dim              )
      .function("pair_geom1"            , &Model::pair_geom1            )
      .function("pair_geom2"            , &Model::pair_geom2            )
      .function("pair_signature"        , &Model::pair_signature        )
      .function("pair_solref"           , &Model::pair_solref           )
      .function("pair_solimp"           , &Model::pair_solimp           )
      .function("pair_margin"           , &Model::pair_margin           )
      .function("pair_gap"              , &Model::pair_gap              )
      .function("pair_friction"         , &Model::pair_friction         )
      .function("exclude_signature"     , &Model::exclude_signature     )
      .function("eq_type"               , &Model::eq_type               )
      .function("eq_obj1id"             , &Model::eq_obj1id             )
      .function("eq_obj2id"             , &Model::eq_obj2id             )
      .function("eq_active"             , &Model::eq_active             )
      .function("eq_solref"             , &Model::eq_solref             )
      .function("eq_solimp"             , &Model::eq_solimp             )
      .function("eq_data"               , &Model::eq_data               )
      .function("tendon_adr"            , &Model::tendon_adr            )
      .function("tendon_num"            , &Model::tendon_num            )
      .function("tendon_matid"          , &Model::tendon_matid          )
      .function("tendon_group"          , &Model::tendon_group          )
      .function("tendon_limited"        , &Model::tendon_limited        )
      .function("tendon_width"          , &Model::tendon_width          )
      .function("tendon_solref_lim"     , &Model::tendon_solref_lim     )
      .function("tendon_solimp_lim"     , &Model::tendon_solimp_lim     )
      .function("tendon_solref_fri"     , &Model::tendon_solref_fri     )
      .function("tendon_solimp_fri"     , &Model::tendon_solimp_fri     )
      .function("tendon_range"          , &Model::tendon_range          )
      .function("tendon_margin"         , &Model::tendon_margin         )
      .function("tendon_stiffness"      , &Model::tendon_stiffness      )
      .function("tendon_damping"        , &Model::tendon_damping        )
      .function("tendon_frictionloss"   , &Model::tendon_frictionloss   )
      .function("tendon_lengthspring"   , &Model::tendon_lengthspring   )
      .function("tendon_length0"        , &Model::tendon_length0        )
      .function("tendon_invweight0"     , &Model::tendon_invweight0     )
      .function("tendon_user"           , &Model::tendon_user           )
      .function("tendon_rgba"           , &Model::tendon_rgba           )
      .function("wrap_type"             , &Model::wrap_type             )
      .function("wrap_objid"            , &Model::wrap_objid            )
      .function("wrap_prm"              , &Model::wrap_prm              )
      .function("actuator_trntype"      , &Model::actuator_trntype      )
      .function("actuator_dyntype"      , &Model::actuator_dyntype      )
      .function("actuator_gaintype"     , &Model::actuator_gaintype     )
      .function("actuator_biastype"     , &Model::actuator_biastype     )
      .function("actuator_trnid"        , &Model::actuator_trnid        )
      .function("actuator_actadr"       , &Model::actuator_actadr       )
      .function("actuator_actnum"       , &Model::actuator_actnum       )
      .function("actuator_group"        , &Model::actuator_group        )
      .function("actuator_ctrllimited"  , &Model::actuator_ctrllimited  )
      .function("actuator_forcelimited" , &Model::actuator_forcelimited )
      .function("actuator_actlimited"   , &Model::actuator_actlimited   )
      .function("actuator_dynprm"       , &Model::actuator_dynprm       )
      .function("actuator_gainprm"      , &Model::actuator_gainprm      )
      .function("actuator_biasprm"      , &Model::actuator_biasprm      )
      .function("actuator_ctrlrange"    , &Model::actuator_ctrlrange    )
      .function("actuator_forcerange"   , &Model::actuator_forcerange   )
      .function("actuator_actrange"     , &Model::actuator_actrange     )
      .function("actuator_gear"         , &Model::actuator_gear         )
      .function("actuator_cranklength"  , &Model::actuator_cranklength  )
      .function("actuator_acc0"         , &Model::actuator_acc0         )
      .function("actuator_length0"      , &Model::actuator_length0      )
      .function("actuator_lengthrange"  , &Model::actuator_lengthrange  )
      .function("actuator_user"         , &Model::actuator_user         )
      .function("actuator_plugin"       , &Model::actuator_plugin       )
      .function("sensor_type"           , &Model::sensor_type           )
      .function("sensor_datatype"       , &Model::sensor_datatype       )
      .function("sensor_needstage"      , &Model::sensor_needstage      )
      .function("sensor_objtype"        , &Model::sensor_objtype        )
      .function("sensor_objid"          , &Model::sensor_objid          )
      .function("sensor_reftype"        , &Model::sensor_reftype        )
      .function("sensor_refid"          , &Model::sensor_refid          )
      .function("sensor_dim"            , &Model::sensor_dim            )
      .function("sensor_adr"            , &Model::sensor_adr            )
      .function("sensor_cutoff"         , &Model::sensor_cutoff         )
      .function("sensor_noise"          , &Model::sensor_noise          )
      .function("sensor_user"           , &Model::sensor_user           )
      .function("sensor_plugin"         , &Model::sensor_plugin         )
      .function("plugin"                , &Model::plugin                )
      .function("plugin_stateadr"       , &Model::plugin_stateadr       )
      .function("plugin_statenum"       , &Model::plugin_statenum       )
      .function("plugin_attr"           , &Model::plugin_attr           )
      .function("plugin_attradr"        , &Model::plugin_attradr        )
      .function("numeric_adr"           , &Model::numeric_adr           )
      .function("numeric_size"          , &Model::numeric_size          )
      .function("numeric_data"          , &Model::numeric_data          )
      .function("text_adr"              , &Model::text_adr              )
      .function("text_size"             , &Model::text_size             )
      .function("text_data"             , &Model::text_data             )
      .function("tuple_adr"             , &Model::tuple_adr             )
      .function("tuple_size"            , &Model::tuple_size            )
      .function("tuple_objtype"         , &Model::tuple_objtype         )
      .function("tuple_objid"           , &Model::tuple_objid           )
      .function("tuple_objprm"          , &Model::tuple_objprm          )
      .function("key_time"              , &Model::key_time              )
      .function("key_qpos"              , &Model::key_qpos              )
      .function("key_qvel"              , &Model::key_qvel              )
      .function("key_act"               , &Model::key_act               )
      .function("key_mpos"              , &Model::key_mpos              )
      .function("key_mquat"             , &Model::key_mquat             )
      .function("key_ctrl"              , &Model::key_ctrl              )
      .function("name_bodyadr"          , &Model::name_bodyadr          )
      .function("name_jntadr"           , &Model::name_jntadr           )
      .function("name_geomadr"          , &Model::name_geomadr          )
      .function("name_siteadr"          , &Model::name_siteadr          )
      .function("name_camadr"           , &Model::name_camadr           )
      .function("name_lightadr"         , &Model::name_lightadr         )
      .function("name_meshadr"          , &Model::name_meshadr          )
      .function("name_skinadr"          , &Model::name_skinadr          )
      .function("name_hfieldadr"        , &Model::name_hfieldadr        )
      .function("name_texadr"           , &Model::name_texadr           )
      .function("name_matadr"           , &Model::name_matadr           )
      .function("name_pairadr"          , &Model::name_pairadr          )
      .function("name_excludeadr"       , &Model::name_excludeadr       )
      .function("name_eqadr"            , &Model::name_eqadr            )
      .function("name_tendonadr"        , &Model::name_tendonadr        )
      .function("name_actuatoradr"      , &Model::name_actuatoradr      )
      .function("name_sensoradr"        , &Model::name_sensoradr        )
      .function("name_numericadr"       , &Model::name_numericadr       )
      .function("name_textadr"          , &Model::name_textadr          )
      .function("name_tupleadr"         , &Model::name_tupleadr         )
      .function("name_keyadr"           , &Model::name_keyadr           )
      .function("name_pluginadr"        , &Model::name_pluginadr        )
      .function("names"                 , &Model::names                 )
;

  class_<State>("State")
      .constructor<Model>()
      .function("ptr"   , &State::ptr, allow_raw_pointers())
      .function("getVal", &State::getVal);

  class_<Simulation>("Simulation")
      .constructor<Model *, State *>()
      .function("state"     , &Simulation::state, allow_raw_pointers())
      .function("model"     , &Simulation::model, allow_raw_pointers())
      .function("applyForce", &Simulation::applyForce)
      .function("applyPose" , &Simulation::applyPose)
      // MJDATA_BINDINGS
      .function("qpos"                  , &Simulation::qpos                  )
      .function("qvel"                  , &Simulation::qvel                  )
      .function("act"                   , &Simulation::act                   )
      .function("qacc_warmstart"        , &Simulation::qacc_warmstart        )
      .function("plugin_state"          , &Simulation::plugin_state          )
      .function("ctrl"                  , &Simulation::ctrl                  )
      .function("qfrc_applied"          , &Simulation::qfrc_applied          )
      .function("xfrc_applied"          , &Simulation::xfrc_applied          )
      .function("mocap_pos"             , &Simulation::mocap_pos             )
      .function("mocap_quat"            , &Simulation::mocap_quat            )
      .function("qacc"                  , &Simulation::qacc                  )
      .function("act_dot"               , &Simulation::act_dot               )
      .function("userdata"              , &Simulation::userdata              )
      .function("sensordata"            , &Simulation::sensordata            )
      .function("plugin"                , &Simulation::plugin                )
      .function("plugin_data"           , &Simulation::plugin_data           )
      .function("xpos"                  , &Simulation::xpos                  )
      .function("xquat"                 , &Simulation::xquat                 )
      .function("xmat"                  , &Simulation::xmat                  )
      .function("xipos"                 , &Simulation::xipos                 )
      .function("ximat"                 , &Simulation::ximat                 )
      .function("xanchor"               , &Simulation::xanchor               )
      .function("xaxis"                 , &Simulation::xaxis                 )
      .function("geom_xpos"             , &Simulation::geom_xpos             )
      .function("geom_xmat"             , &Simulation::geom_xmat             )
      .function("site_xpos"             , &Simulation::site_xpos             )
      .function("site_xmat"             , &Simulation::site_xmat             )
      .function("cam_xpos"              , &Simulation::cam_xpos              )
      .function("cam_xmat"              , &Simulation::cam_xmat              )
      .function("light_xpos"            , &Simulation::light_xpos            )
      .function("light_xdir"            , &Simulation::light_xdir            )
      .function("subtree_com"           , &Simulation::subtree_com           )
      .function("cdof"                  , &Simulation::cdof                  )
      .function("cinert"                , &Simulation::cinert                )
      .function("ten_wrapadr"           , &Simulation::ten_wrapadr           )
      .function("ten_wrapnum"           , &Simulation::ten_wrapnum           )
      .function("ten_J_rownnz"          , &Simulation::ten_J_rownnz          )
      .function("ten_J_rowadr"          , &Simulation::ten_J_rowadr          )
      .function("ten_J_colind"          , &Simulation::ten_J_colind          )
      .function("ten_length"            , &Simulation::ten_length            )
      .function("ten_J"                 , &Simulation::ten_J                 )
      .function("wrap_obj"              , &Simulation::wrap_obj              )
      .function("wrap_xpos"             , &Simulation::wrap_xpos             )
      .function("actuator_length"       , &Simulation::actuator_length       )
      .function("actuator_moment"       , &Simulation::actuator_moment       )
      .function("crb"                   , &Simulation::crb                   )
      .function("qM"                    , &Simulation::qM                    )
      .function("qLD"                   , &Simulation::qLD                   )
      .function("qLDiagInv"             , &Simulation::qLDiagInv             )
      .function("qLDiagSqrtInv"         , &Simulation::qLDiagSqrtInv         )
      .function("ten_velocity"          , &Simulation::ten_velocity          )
      .function("actuator_velocity"     , &Simulation::actuator_velocity     )
      .function("cvel"                  , &Simulation::cvel                  )
      .function("cdof_dot"              , &Simulation::cdof_dot              )
      .function("qfrc_bias"             , &Simulation::qfrc_bias             )
      .function("qfrc_passive"          , &Simulation::qfrc_passive          )
      .function("subtree_linvel"        , &Simulation::subtree_linvel        )
      .function("subtree_angmom"        , &Simulation::subtree_angmom        )
      .function("qH"                    , &Simulation::qH                    )
      .function("qHDiagInv"             , &Simulation::qHDiagInv             )
      .function("D_rownnz"              , &Simulation::D_rownnz              )
      .function("D_rowadr"              , &Simulation::D_rowadr              )
      .function("D_colind"              , &Simulation::D_colind              )
      .function("qDeriv"                , &Simulation::qDeriv                )
      .function("qLU"                   , &Simulation::qLU                   )
      .function("actuator_force"        , &Simulation::actuator_force        )
      .function("qfrc_actuator"         , &Simulation::qfrc_actuator         )
      .function("qfrc_smooth"           , &Simulation::qfrc_smooth           )
      .function("qacc_smooth"           , &Simulation::qacc_smooth           )
      .function("qfrc_constraint"       , &Simulation::qfrc_constraint       )
      .function("qfrc_inverse"          , &Simulation::qfrc_inverse          )
      .function("cacc"                  , &Simulation::cacc                  )
      .function("cfrc_int"              , &Simulation::cfrc_int              )
      .function("cfrc_ext"              , &Simulation::cfrc_ext              )
      .function("freeLastXML"           , &Simulation::freeLastXML           )
      .function("step"                  , &Simulation::step                  )
      .function("step1"                 , &Simulation::step1                 )
      .function("step2"                 , &Simulation::step2                 )
      .function("forward"               , &Simulation::forward               )
      .function("inverse"               , &Simulation::inverse               )
      .function("forwardSkip"           , &Simulation::forwardSkip           )
      .function("inverseSkip"           , &Simulation::inverseSkip           )
      .function("defaultSolRefImp"      , &Simulation::defaultSolRefImp      , allow_raw_pointers())
      .function("sizeModel"             , &Simulation::sizeModel             )
      .function("resetData"             , &Simulation::resetData             )
      .function("resetDataDebug"        , &Simulation::resetDataDebug        )
      .function("resetDataKeyframe"     , &Simulation::resetDataKeyframe     )
      .function("deleteData"            , &Simulation::deleteData            )
      .function("resetCallbacks"        , &Simulation::resetCallbacks        )
      .function("printFormattedModel"   , &Simulation::printFormattedModel   )
      .function("printModel"            , &Simulation::printModel            )
      .function("printFormattedData"    , &Simulation::printFormattedData    )
      .function("printData"             , &Simulation::printData             )
      .function("_printMat"             , &Simulation::_printMat             , allow_raw_pointers())
      .function("fwdPosition"           , &Simulation::fwdPosition           )
      .function("fwdVelocity"           , &Simulation::fwdVelocity           )
      .function("fwdActuation"          , &Simulation::fwdActuation          )
      .function("fwdAcceleration"       , &Simulation::fwdAcceleration       )
      .function("fwdConstraint"         , &Simulation::fwdConstraint         )
      .function("Euler"                 , &Simulation::Euler                 )
      .function("RungeKutta"            , &Simulation::RungeKutta            )
      .function("invPosition"           , &Simulation::invPosition           )
      .function("invVelocity"           , &Simulation::invVelocity           )
      .function("invConstraint"         , &Simulation::invConstraint         )
      .function("compareFwdInv"         , &Simulation::compareFwdInv         )
      .function("sensorPos"             , &Simulation::sensorPos             )
      .function("sensorVel"             , &Simulation::sensorVel             )
      .function("sensorAcc"             , &Simulation::sensorAcc             )
      .function("energyPos"             , &Simulation::energyPos             )
      .function("energyVel"             , &Simulation::energyVel             )
      .function("checkPos"              , &Simulation::checkPos              )
      .function("checkVel"              , &Simulation::checkVel              )
      .function("checkAcc"              , &Simulation::checkAcc              )
      .function("kinematics"            , &Simulation::kinematics            )
      .function("comPos"                , &Simulation::comPos                )
      .function("camlight"              , &Simulation::camlight              )
      .function("tendon"                , &Simulation::tendon                )
      .function("transmission"          , &Simulation::transmission          )
      .function("crbCalculate"          , &Simulation::crbCalculate          )
      .function("factorM"               , &Simulation::factorM               )
      .function("solveM"                , &Simulation::solveM                , allow_raw_pointers())
      .function("solveM2"               , &Simulation::solveM2               , allow_raw_pointers())
      .function("comVel"                , &Simulation::comVel                )
      .function("passive"               , &Simulation::passive               )
      .function("subtreeVel"            , &Simulation::subtreeVel            )
      .function("rne"                   , &Simulation::rne                   , allow_raw_pointers())
      .function("rnePostConstraint"     , &Simulation::rnePostConstraint     )
      .function("collision"             , &Simulation::collision             )
      .function("makeConstraint"        , &Simulation::makeConstraint        )
      .function("projectConstraint"     , &Simulation::projectConstraint     )
      .function("referenceConstraint"   , &Simulation::referenceConstraint   )
      .function("isPyramidal"           , &Simulation::isPyramidal           )
      .function("isSparse"              , &Simulation::isSparse              )
      .function("isDual"                , &Simulation::isDual                )
      .function("mulJacVec"             , &Simulation::mulJacVec             , allow_raw_pointers())
      .function("mulJacTVec"            , &Simulation::mulJacTVec            , allow_raw_pointers())
      .function("jacSubtreeCom"         , &Simulation::jacSubtreeCom         , allow_raw_pointers())
      .function("name2id"               , &Simulation::name2id               )
      .function("id2name"               , &Simulation::id2name               )
      .function("fullM"                 , &Simulation::fullM                 , allow_raw_pointers())
      .function("differentiatePos"      , &Simulation::differentiatePos      , allow_raw_pointers())
      .function("integratePos"          , &Simulation::integratePos          , allow_raw_pointers())
      .function("normalizeQuat"         , &Simulation::normalizeQuat         , allow_raw_pointers())
      .function("getTotalmass"          , &Simulation::getTotalmass          )
      .function("getPluginConfig"       , &Simulation::getPluginConfig       )
      .function("loadPluginLibrary"     , &Simulation::loadPluginLibrary     )
      .function("version"               , &Simulation::version               )
      .function("versionString"         , &Simulation::versionString         )
      .function("_rectangle"            , &Simulation::_rectangle            )
      .function("_finish"               , &Simulation::_finish               )
      .function("_getError"             , &Simulation::_getError             )
      .function("i_themeSpacing"        , &Simulation::i_themeSpacing        )
      .function("i_themeColor"          , &Simulation::i_themeColor          )
      .function("_error"                , &Simulation::_error                )
      .function("_error_i"              , &Simulation::_error_i              )
      .function("_error_s"              , &Simulation::_error_s              )
      .function("_warning"              , &Simulation::_warning              )
      .function("_warning_i"            , &Simulation::_warning_i            )
      .function("_warning_s"            , &Simulation::_warning_s            )
      .function("_clearHandlers"        , &Simulation::_clearHandlers        )
      .function("warning"               , &Simulation::warning               )
      .function("_writeLog"             , &Simulation::_writeLog             )
      .function("activate"              , &Simulation::activate              )
      .function("deactivate"            , &Simulation::deactivate            )
      .function("_zero"                 , &Simulation::_zero                 , allow_raw_pointers())
      .function("_fill"                 , &Simulation::_fill                 , allow_raw_pointers())
      .function("_copy"                 , &Simulation::_copy                 , allow_raw_pointers())
      .function("_sum"                  , &Simulation::_sum                  , allow_raw_pointers())
      .function("_L1"                   , &Simulation::_L1                   , allow_raw_pointers())
      .function("_scl"                  , &Simulation::_scl                  , allow_raw_pointers())
      .function("_add"                  , &Simulation::_add                  , allow_raw_pointers())
      .function("_sub"                  , &Simulation::_sub                  , allow_raw_pointers())
      .function("_addTo"                , &Simulation::_addTo                , allow_raw_pointers())
      .function("_subFrom"              , &Simulation::_subFrom              , allow_raw_pointers())
      .function("_addToScl"             , &Simulation::_addToScl             , allow_raw_pointers())
      .function("_addScl"               , &Simulation::_addScl               , allow_raw_pointers())
      .function("_normalize"            , &Simulation::_normalize            , allow_raw_pointers())
      .function("_norm"                 , &Simulation::_norm                 , allow_raw_pointers())
      .function("_dot"                  , &Simulation::_dot                  , allow_raw_pointers())
      .function("_mulMatVec"            , &Simulation::_mulMatVec            , allow_raw_pointers())
      .function("_mulMatTVec"           , &Simulation::_mulMatTVec           , allow_raw_pointers())
      .function("_mulVecMatVec"         , &Simulation::_mulVecMatVec         , allow_raw_pointers())
      .function("_transpose"            , &Simulation::_transpose            , allow_raw_pointers())
      .function("_symmetrize"           , &Simulation::_symmetrize           , allow_raw_pointers())
      .function("_eye"                  , &Simulation::_eye                  , allow_raw_pointers())
      .function("_mulMatMat"            , &Simulation::_mulMatMat            , allow_raw_pointers())
      .function("_mulMatMatT"           , &Simulation::_mulMatMatT           , allow_raw_pointers())
      .function("_mulMatTMat"           , &Simulation::_mulMatTMat           , allow_raw_pointers())
      .function("_sqrMatTD"             , &Simulation::_sqrMatTD             , allow_raw_pointers())
      .function("_cholFactor"           , &Simulation::_cholFactor           , allow_raw_pointers())
      .function("_cholSolve"            , &Simulation::_cholSolve            , allow_raw_pointers())
      .function("_cholUpdate"           , &Simulation::_cholUpdate           , allow_raw_pointers())
      .function("_encodePyramid"        , &Simulation::_encodePyramid        , allow_raw_pointers())
      .function("_decodePyramid"        , &Simulation::_decodePyramid        , allow_raw_pointers())
      .function("_springDamper"         , &Simulation::_springDamper         )
      .function("_min"                  , &Simulation::_min                  )
      .function("_max"                  , &Simulation::_max                  )
      .function("_clip"                 , &Simulation::_clip                 )
      .function("_sign"                 , &Simulation::_sign                 )
      .function("_round"                , &Simulation::_round                )
      .function("_type2Str"             , &Simulation::_type2Str             )
      .function("_str2Type"             , &Simulation::_str2Type             )
      .function("_writeNumBytes"        , &Simulation::_writeNumBytes        )
      .function("_warningText"          , &Simulation::_warningText          )
      .function("_isBad"                , &Simulation::_isBad                )
      .function("_isZero"               , &Simulation::_isZero               , allow_raw_pointers())
      .function("_standardNormal"       , &Simulation::_standardNormal       , allow_raw_pointers())
      .function("_insertionSort"        , &Simulation::_insertionSort        , allow_raw_pointers())
      .function("_Halton"               , &Simulation::_Halton               )
      .function("_sigmoid"              , &Simulation::_sigmoid              )
      .function("_transitionFD"         , &Simulation::_transitionFD         , allow_raw_pointers())
      .function("_pluginCount"          , &Simulation::_pluginCount          )
      ;

  value_object<mjModel>("mjModel")
      .field("ngeom"      , &mjModel::ngeom)
      .field("nq"         , &mjModel::nq)
      .field("na"         , &mjModel::na)
      .field("nv"         , &mjModel::nv)
      .field("nu"         , &mjModel::nu)
      .field("nbody"      , &mjModel::nbody)
      .field("nsensordata", &mjModel::nsensordata)
      //.field("body_rootid", &mjModel::body_rootid, allow_raw_pointers())
      .field("nmesh"      , &mjModel::nmesh)
      .field("nmeshvert"  , &mjModel::nmeshvert)
      .field("nmeshface"  , &mjModel::nmeshface);

  value_object<mjvPerturb>("mjvPerturb")
      .field("select"    , &mjvPerturb::select)     // selected body id; non-positive: none
      .field("skinselect", &mjvPerturb::skinselect) // selected skin id; negative: none
      .field("active"    , &mjvPerturb::active)     // perturbation bitmask (mjtPertBit)
      .field("active2"   , &mjvPerturb::active2)    // secondary perturbation bitmask (mjtPertBit)
      .field("refpos"    , &mjvPerturb::refpos)     // desired position for selected object
      .field("refquat"   , &mjvPerturb::refquat)    // desired orientation for selected object
      .field("localpos"  , &mjvPerturb::localpos)   // selection point in object coordinates
      .field("scale"     , &mjvPerturb::scale)      // relative mouse motion-to-space scaling (set by initPerturb)
      ;

  value_object<mjContact>("mjContact")
      .field("dist"         , &mjContact::dist)             // distance between nearest points; neg: penetration
      .field("pos"          , &mjContact::pos)              // position of contact point: midpoint between geoms
      .field("frame"        , &mjContact::frame)            // normal is in [0-2]
      .field("includemargin", &mjContact::includemargin)    // include if dist<includemargin=margin-gap
      .field("friction"     , &mjContact::friction)         // tangent1, 2, spin, roll1, 2
      .field("solref"       , &mjContact::solref)           // constraint solver reference
      .field("solimp"       , &mjContact::solimp)           // constraint solver impedance
      .field("mu"           , &mjContact::mu)               // friction of regularized cone, set by mj_makeConstraint
      .field("H"            , &mjContact::H)                // cone Hessian, set by mj_updateConstraint
      .field("dim"          , &mjContact::H)                // contact space dimensionality: 1, 3, 4 or 6
      .field("geom1"        , &mjContact::H)                // id of geom 1
      .field("geom2"        , &mjContact::H)                // id of geom 2
      .field("exclude"      , &mjContact::exclude)          // 0: include, 1: in gap, 2: fused, 3: equality, 4: no dofs
      .field("efc_address"  , &mjContact::efc_address);     // address in efc; -1: not included, -2-i: distance constraint i

  value_object<mjLROpt>("mjLROpt")
      .field("mode"       , &mjLROpt::mode)
      .field("useexisting", &mjLROpt::useexisting)
      .field("uselimit"   , &mjLROpt::uselimit)
      .field("accel"      , &mjLROpt::accel)      // target acceleration used to compute force
      .field("maxforce"   , &mjLROpt::maxforce)   // maximum force; 0: no limit
      .field("timeconst"  , &mjLROpt::timeconst)  // time constant for velocity reduction; min 0.01
      .field("timestep"   , &mjLROpt::timestep)   // simulation timestep; 0: use mjOption.timestep
      .field("inttotal"   , &mjLROpt::inttotal)   // total simulation time interval
      .field("inteval"    , &mjLROpt::inteval)    // evaluation time interval (at the end)
      .field("tolrange"   , &mjLROpt::tolrange);  // convergence tolerance (relative to range)

  value_object<mjOption>("mjOption")
      .field("timestep"            , &mjOption::timestep)          // timestep
      .field("apirate"             , &mjOption::apirate)           // update rate for remote API (Hz)
      .field("impratio"            , &mjOption::impratio)          // ratio of friction-to-normal contact impedance
      .field("tolerance"           , &mjOption::tolerance)         // main solver tolerance
      .field("noslip_tolerance"    , &mjOption::noslip_tolerance)  // noslip solver tolerance
      .field("mpr_tolerance"       , &mjOption::mpr_tolerance)     // MPR solver tolerance
      //.field("gravity"           , &mjOption::gravity)           // gravitational acceleration
      //.field("wind"              , &mjOption::wind)              // wind (for lift, drag and viscosity)
      //.field("magnetic"          , &mjOption::magnetic)          // global magnetic flux
      .field("density"             , &mjOption::density)           // density of medium
      .field("viscosity"           , &mjOption::viscosity)         // viscosity of medium
      .field("o_margin"            , &mjOption::o_margin)          // margin
      //.field("o_solref"          , &mjOption::o_solref)          // solref
      //.field("o_solimp"          , &mjOption::o_solimp)          // solimp
      .field("integrator"          , &mjOption::integrator)        // integration mode (mjtIntegrator)
      .field("collision"           , &mjOption::collision)         // collision mode (mjtCollision)
      .field("cone"                , &mjOption::cone)              // type of friction cone (mjtCone)
      .field("jacobian"            , &mjOption::jacobian)          // type of Jacobian (mjtJacobian)
      .field("solver"              , &mjOption::solver)            // solver algorithm (mjtSolver)
      .field("iterations"          , &mjOption::iterations)        // maximum number of main solver iterations
      .field("noslip_iterations"   , &mjOption::noslip_iterations) // maximum number of noslip solver iterations
      .field("mpr_iterations"      , &mjOption::mpr_iterations)    // maximum number of MPR solver iterations
      .field("disableflags"        , &mjOption::disableflags)      // bit flags for disabling standard features
      .field("enableflags"         , &mjOption::enableflags);      // bit flags for enabling optional features

  register_vector<mjContact>("vector<mjContact>");
}
