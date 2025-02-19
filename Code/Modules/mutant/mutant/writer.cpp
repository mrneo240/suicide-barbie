#include "writer.h"
#include "clip.h"
#include "bundle.h"

namespace mutant
{

mutant_writer::mutant_writer( std::auto_ptr<binary_output> output )
:	binary_output_utils( output ) {
}

mutant_writer::~mutant_writer()
{
}


void mutant_writer::write( anim_character_set& char_set )
{
	try
	{
		// write char count
		writeDword( char_set.size() );

		anim_character_set::char_it_t it = char_set.iterate();
		for( ; it; ++it )
		{
			std::string const& char_name = it->first;
			anim_character* character = it->second;

			assert( character );

			writeCharacterData( char_name, *character );
		}
	} catch( EIoEof& ) {
		mutant_throw( "Unexpected end-of-file (file may be corrupted)" );
	} catch( EIoError& ) {
		mutant_throw( "Read/write error" );
	}
}
/*
void mutant_writer::write( data::base_mesh const& mesh )
{
	try
	{
		writeDword( mesh.vertexCount );
		writeDword( mesh.vertexDataSize );
		writeDword( mesh.vertexStride );
		writeData ( mesh.vertexData, mesh.vertexDataSize );

		writeDword( mesh.indexCount );
		writeDword( mesh.indexSize );
		writeData ( mesh.indexData, mesh.indexCount * mesh.indexSize );

	} catch( EIoEof& ) {
		mutant_throw( "Unexpected end-of-file (file may be corrupted)" );
	} catch( EIoError& ) {
		mutant_throw( "Read/write error" );
	}
}

void mutant_writer::write( data::dx9_mesh const& mesh )
{
	try
	{
		write( mesh.base() );
		writeDword( mesh.fvfVertexDecl );
		writeDword( mesh.primitiveType );

		writeBool( (mesh.skinInfo != 0) );
		if( mesh.skinInfo )
			write( *mesh.skinInfo );

	} catch( EIoEof& ) {
		mutant_throw( "Unexpected end-of-file (file may be corrupted)" );
	} catch( EIoError& ) {
		mutant_throw( "Read/write error" );
	}
}

void mutant_writer::write( data::skin_info const& skin )
{
	try
	{
		writeDword( skin.weightsPerVertex );
		writeDword( skin.boneCount );
		for( size_t q = 0; q < skin.boneCount; ++q )
		{
			writeType( skin.bones[q].matrix );
			writeString( skin.bones[q].name );
		}

	} catch( EIoEof& ) {
		mutant_throw( "Unexpected end-of-file (file may be corrupted)" );
	} catch( EIoError& ) {
		mutant_throw( "Read/write error" );
	}
}
*/

/*
namespace {
	unsigned blitRef( std::string const& names, simple_scene::Ref const& ref )
	{
		return unsigned(reinterpret_cast<std::string::value_type*>(ref.data) - &names[0]);
	}

	std::vector<unsigned> blitRefs( std::string const& names, simple_scene::Ref* refs, size_t count )
	{
		std::vector<unsigned> data( count );
		for(size_t q = 0; q < count; ++q )
			data[q] = blitRef( names, refs[q] );
		return data;
	}
}*/
/*
void mutant_writer::write( simple_scene const& scene )
{
	try
	{
//		writeString( scene.meshIds );
//		writeString( scene.clipIds );
//		writeString( scene.nodeNames );
//
//		size_t nodeNamesRefDataIt = 0;

		// meshes
		writeDword( scene.meshCount );
//		writeData( blitRefs( scene.meshIds, scene.meshes, scene.meshCount ).begin(), scene.meshCount );
		writeData( scene.meshIds, scene.meshCount );

		// lights
		writeDword( scene.lightCount );
		for( size_t q = 0; q < scene.lightCount; ++q )
		{
//			writeType( blitRef( scene.nodeNames, scene.lights[q].nodeName ) );
			writeString( scene.lights[q].nodeName );
			writeType( scene.lights[q].worldMatrix );
		}

		// cameras
		writeDword( scene.cameraCount );
		for( size_t q = 0; q < scene.cameraCount; ++q )
		{
//			writeType( blitRef( scene.nodeNames, scene.cameras[q].nodeName ) );
			writeString( scene.cameras[q].nodeName );
			writeType( scene.cameras[q].worldMatrix );
		}
		writeDword( scene.defaultCameraIndex );

		// actors
		writeDword( scene.actorCount );
		for( size_t q = 0; q < scene.actorCount; ++q )
		{
//			writeType( blitRef( scene.nodeNames, scene.actors[q].nodeName ) );
			writeString( scene.actors[q].nodeName );
			writeType( scene.actors[q].worldMatrix );
			writeDword( scene.actors[q].meshIndex );
		}

		// clips
//		writeDword( scene.clipCount );
//		writeData( blitRefs( scene.clipIds, scene.clips, scene.clipCount ).begin(), scene.clipCount );
		writeString( scene.animCharId );
		writeDword( scene.defaultClipIndex );

	} catch( EIoEof& ) {
		mutant_throw( "Unexpected end-of-file (file may be corrupted)" );
	} catch( EIoError& ) {
		mutant_throw( "Read/write error" );
	}
}
*/
void mutant_writer::writeCharacterData( std::string const& char_name, anim_character& anim_char )
{
	writeString( char_name );

	writeDword( anim_char.size_hierarchy() ); // hierarchy count
	writeDword( anim_char.size() ); // clip count

	for( anim_character::hierarchy_it_t it = anim_char.iterate_hierarchies(); it; ++it )
	{
		anim_hierarchy* hier = *it;

		assert( hier );

		writeHierarchyData( *hier );
	}

	for( anim_character::clips_it_t it = anim_char.iterate(); it; ++it )
	{
		std::string const& clip_name = it->first;
		anim_clip* clip = it->second;

		assert( clip );

		writeClipData( clip_name, *clip );
	}
}

void mutant_writer::writeHierarchyData( anim_hierarchy& hier )
{
	writeString( hier.name() );
	writeDword( hier.size() );

	for( anim_hierarchy::node_it_t it = hier.iterate(); it; ++it )
	{
		writeString( it->name );
		writeDword( it->children.size() );
		writeData( anim_hierarchy::node::children_it_t( it->children.begin(), it->children.end() ) );
	}
}

void mutant_writer::writeClipData( std::string const& clip_name, anim_clip& clip )
{
	writeString( clip_name );
	writeDword( clip.flags() );
	writeType<float>( clip.clip_length() );
	writeDword( clip.size() ); // bundle count

	for( anim_clip::iterator_t it = clip.iterate(); it; ++it )
	{
		std::string const& bundle_name = it->first;
		anim_bundle* bundle = it->second;

		writeBundleData( bundle_name, *bundle );
	}
}

void mutant_writer::writeBundleData( std::string const& bundle_name, anim_bundle& bundle )
{
	writeString( bundle_name );

	unsigned anim_count = bundle.size_ff() + bundle.size_fs();
	writeDword( anim_count );

	for( anim_bundle::iterator_ff_t it = bundle.iterate_ff(); it; ++it )
		writeAnimationData( it->first, it->second, ANIM_FLOAT );

	for( anim_bundle::iterator_fs_t it = bundle.iterate_fs(); it; ++it )
		writeAnimationData( it->first, it->second, ANIM_STRING );
}

}
